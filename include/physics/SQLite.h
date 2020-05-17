#ifndef PHYSICS_SQLITEDATABASE_H
#define PHYSICS_SQLITEDATABASE_H

#include "IDataBase.h"
#include <sqlite3.h>

constexpr int USER_ALREADY_EXISTS = -2;
constexpr int USER_NOT_FOUND = -1;
constexpr int SUCCESS = 0;

/*
class SQLiteDataBase : AbstractDataBase {
public:
	SQLiteDataBase() {
		connectToDataBase();
		createTable();
		selectResult = std::make_tuple(-1, "null", "null", -1, -1);
		status = USER_NOT_FOUND;
	};
	
	~SQLiteDataBase() {
		sqlite3_close(db);
	};
	
	int getAuthorizeUser(const string &nickName, const string &passwd) override {
		sqlQuery = "SELECT * FROM USERS WHERE Name='" + nickName + "' AND Password='" + passwd + '\'';
		if (selectInfo() == SUCCESS)
			return getUserId(); // id
		return USER_NOT_FOUND;
	};
	
	const std::tuple<vector<string>, vector<int>, vector<int>> &getStandings(int topCount) override {
		sqlite3_stmt *stmt = nullptr;
		
		if (status == SUCCESS) {
			std::get<0>(topTable).clear();
			std::get<1>(topTable).clear();
			std::get<2>(topTable).clear();
		}
		sqlQuery = "SELECT Name, LocalScore, NetworkScore FROM USERS ORDER BY (LocalScore + NetworkScore) DESC LIMIT " +
				   std::to_string(topCount);
		int rez = sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &stmt, nullptr);
		if (rez != SQLITE_OK)
			throw std::runtime_error(string("Error in Sql query: " + string(sqlite3_errmsg(db))));
		while ((rez = sqlite3_step(stmt)) == SQLITE_ROW) {
			std::get<0>(topTable).emplace_back((char *) sqlite3_column_text(stmt, 0));
			std::get<1>(topTable).push_back(sqlite3_column_int(stmt, 1));
			std::get<2>(topTable).push_back(sqlite3_column_int(stmt, 2));
		}
		if (rez != SQLITE_ROW && rez != SQLITE_DONE) {
			sqlite3_finalize(stmt);
			throw std::runtime_error(sqlite3_errmsg(db));
		}
		sqlite3_finalize(stmt);
		return topTable;
	};
	
	const string &getUserNickname() override { return std::get<1>(selectResult); }
	
	int deleteUser() override {
		if (status == USER_NOT_FOUND) // пользователя можно удалить, только будучи авторизованным
			return USER_NOT_FOUND;
		sqlQuery = "DELETE FROM USERS WHERE ID=" + std::to_string(getUserId());
		return queryExecutor();
	};
	
	int setUser(const string &nickName, const string &passwd) override {
		sqlite3_stmt *stmt = nullptr;
		sqlQuery = "SELECT Name FROM USERS WHERE Name='" + nickName + '\'';
		if (findUser(&stmt)) {
			sqlite3_finalize(stmt);
			return USER_ALREADY_EXISTS;
		}
		sqlQuery = "INSERT INTO USERS (Id, Name, Password, NetworkScore, LocalScore)"  \
         " VALUES (((SELECT COUNT(Id) FROM USERS) + 1),'" + nickName + "','" + passwd + "',0 ,0);";
		return queryExecutor();
	};
	
	int setUserLocalScore(int local) override {
		sqlQuery = "UPDATE USERS SET LocalScore =" + std::to_string(local) + \
                " WHERE ID=" + std::to_string(getUserId());
		std::get<4>(selectResult) = local;
		return queryExecutor();
	};
	
	int setUserNetworkScore(int global) override {
		sqlQuery = "UPDATE USERS SET NetworkScore =" + std::to_string(global) + \
                " WHERE ID=" + std::to_string(getUserId());
		std::get<3>(selectResult) = global;
		return queryExecutor();
	};
	
	int getUserLocalScore() override { return std::get<4>(selectResult); }
	
	int getUserNetworkScore() override { return std::get<3>(selectResult); }
	
	int getUserId() { return std::get<0>(selectResult); }

private:
	int status;
	std::tuple<int, string, string, int, int> selectResult;
	std::tuple<vector<string>, vector<int>, vector<int>> topTable;
	sqlite3 *db;
	string sqlQuery;
private:
	bool findUser(sqlite3_stmt **stmt);
	int selectInfo();
	int queryExecutor();
	int createTable();
	int connectToDataBase();
};

int SQLiteDataBase::connectToDataBase() {
	int rez = sqlite3_open("dataBase/UserData.db", &db);
	if (rez != SQLITE_OK)
		throw std::runtime_error(string("Error! Can't open dataBase"));
	return (SUCCESS);
}

int SQLiteDataBase::createTable() {
	sqlQuery = "CREATE TABLE IF NOT EXISTS USERS("  \
      "Id           INT PRIMARY KEY	NOT NULL," \
      "Name			CHAR(15)        NOT NULL," \
      "Password     CHAR(15)		NOT NULL," \
      "NetworkScore INT				NOT NULL," \
      "LocalScore   INT				NOT NULL);";
	return queryExecutor();
}

int SQLiteDataBase::queryExecutor() {
	int rez = sqlite3_exec(db, sqlQuery.c_str(), nullptr, nullptr, nullptr);
	if (rez != SQLITE_OK)
		throw std::runtime_error(string("Error in Sql query: " + string(sqlite3_errmsg(db))));
	return SUCCESS;
}

int SQLiteDataBase::selectInfo() {
	sqlite3_stmt *stmt = nullptr;
	
	if (!findUser(&stmt)) { // пользователя не найден
		if (status == SUCCESS) { // если предыдущий сеанс авторизации заполнил кортеж, то необходимо его проинициализировать начальными значениями
			std::get<0>(selectResult) = -1; // id
			std::get<1>(selectResult) = "null"; // name
			std::get<2>(selectResult) = "null"; // passwd
			std::get<3>(selectResult) = -1; // networkScore
			std::get<4>(selectResult) = -1; // localScore
			sqlite3_finalize(stmt);
		}
		return USER_NOT_FOUND;
	} else {
		if (!stmt)
			throw std::runtime_error(string("Broken pointer!"));
		std::get<0>(selectResult) = sqlite3_column_int(stmt, 0); // id
		std::get<1>(selectResult) = (char *) sqlite3_column_text(stmt, 1); // name
		std::get<2>(selectResult) = (char *) sqlite3_column_text(stmt, 2); // passwd
		std::get<3>(selectResult) = sqlite3_column_int(stmt, 3); // networkScore
		std::get<4>(selectResult) = sqlite3_column_int(stmt, 4); // localScore
		status = SUCCESS;
	}
	sqlite3_finalize(stmt);
	return SUCCESS;
}

bool SQLiteDataBase::findUser(sqlite3_stmt **stmt) {
	int rez = sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, stmt, nullptr);
	if (rez != SQLITE_OK)
		throw std::runtime_error(string("Error in Sql query: " + string(sqlite3_errmsg(db))));
	rez = sqlite3_step(*stmt);
	if (rez != SQLITE_ROW && rez != SQLITE_DONE) {
		sqlite3_finalize(*stmt);
		throw std::runtime_error(sqlite3_errmsg(db));
	}
	return rez != SQLITE_DONE;
}*/

class SQLiteDataBase : AbstractDataBase {
public:
	SQLiteDataBase();
	~SQLiteDataBase() override;
	int getAuthorizeUser(const string &nickName, const string &passwd) override;
	const std::tuple<vector<string>, vector<int>, vector<int>> &getStandings(int topCount) override;
	const string &getUserNickname() override;
	int deleteUser() override;
	int setUser(const string &nickName, const string &passwd) override;
	int setUserLocalScore(int local) override;
	int setUserNetworkScore(int global) override;
	int getUserLocalScore() override;
	int getUserNetworkScore() override;
	int getUserId();

private:
	int status;
	std::tuple<int, string, string, int, int> selectResult;
	std::tuple<vector<string>, vector<int>, vector<int>> topTable;
	sqlite3 *db;
	string sqlQuery;
private:
	bool findUser(sqlite3_stmt **stmt);
	int selectInfo();
	int queryExecutor();
	int createTable();
	int connectToDataBase();
};
#endif //PHYSICS_SQLITEDATABASE_H
