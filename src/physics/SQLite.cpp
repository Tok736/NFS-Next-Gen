#include "../include/physics/SQLite.h"
#include <iostream>
using std::string;
using std::vector;

SQLiteDataBase::SQLiteDataBase() {
	connectToDataBase();
	createTable();
	selectResult = std::make_tuple(-1, "null", "null", -1, -1);
	status = USER_NOT_FOUND;
}

SQLiteDataBase::~SQLiteDataBase() {
	sqlite3_close(db);
}

int SQLiteDataBase::getAuthorizeUser(const string &nickName, const string &passwd) {
	string sqlQuery = "SELECT * FROM USERS WHERE Name='" + nickName + "' AND Password='" + passwd + '\'';
	if (getSingle(sqlQuery, FILL) == SUCCESS) {
		status = USER_BEEN_LOGGED;
		return getUserId(); // id
	}
	return USER_NOT_FOUND;
}

const std::tuple<vector<string>, vector<int>, vector<int>> &SQLiteDataBase::getStandings(int topCount) {
	sqlite3_stmt *stmt = nullptr;
	
	std::get<0>(topTable).clear();
	std::get<1>(topTable).clear();
	std::get<2>(topTable).clear();
	string sqlQuery = "SELECT Name, LocalScore1, LocalScore2 FROM USERS ORDER BY (LocalScore1 + LocalScore2) DESC LIMIT " +
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
}

const string &SQLiteDataBase::getUserNickname() { return std::get<1>(selectResult); }

int SQLiteDataBase::deleteUser() {
	if (status != USER_BEEN_LOGGED) // пользователя можно удалить, только будучи авторизованным
		return USER_NOT_FOUND;
	string sqlQuery = "DELETE FROM USERS WHERE ID=" + std::to_string(getUserId());
	return queryExecutor(sqlQuery);
}

int SQLiteDataBase::setUser(const string &nickName, const string &passwd) {
	string sqlQuery = "SELECT Name FROM USERS WHERE Name='" + nickName + '\'';
	if (getSingle(sqlQuery, SEARCH) != USER_NOT_FOUND)
		return USER_ALREADY_EXISTS;
	sqlQuery = "INSERT INTO USERS (Id, Name, Password, LocalScore2, LocalScore1)"  \
         " VALUES (((SELECT COUNT(Id) FROM USERS) + 1),'" + nickName + "','" + passwd + "',0 ,0);";
	return queryExecutor(sqlQuery);
}

int SQLiteDataBase::setUserLocalScore(int local) {
	string sqlQuery = "UPDATE USERS SET LocalScore1 =" + std::to_string(local) + \
                " WHERE ID=" + std::to_string(getUserId());
	std::get<4>(selectResult) = local;
	return queryExecutor(sqlQuery);
}

int SQLiteDataBase::setUserNetworkScore(int global) {
	string sqlQuery = "UPDATE USERS SET LocalScore2 =" + std::to_string(global) + \
                " WHERE ID=" + std::to_string(getUserId());
	std::get<3>(selectResult) = global;
	return queryExecutor(sqlQuery);
}

int SQLiteDataBase::getLastSession() {
	string sqlQuery = "SELECT * FROM USERS WHERE Id=(SELECT LastId FROM LAST_SESSION)";
	if (getSingle(sqlQuery, FILL) != USER_NOT_FOUND)
		return SUCCESS;
	return USER_NOT_FOUND;
}

int SQLiteDataBase::setLastSession() {
	if (status != USER_BEEN_LOGGED)
		return USER_NOT_FOUND;
	string sqlQuery = "INSERT OR REPLACE INTO LAST_SESSION(DefaultId, LastId)"
					  "  VALUES(1, " + std::to_string(getUserId()) + ')';
	return queryExecutor(sqlQuery);
}

int SQLiteDataBase::getUserLocalScore() { return std::get<4>(selectResult); }

int SQLiteDataBase::getUserNetworkScore() { return std::get<3>(selectResult); }

int SQLiteDataBase::getUserId() { return std::get<0>(selectResult); }

int SQLiteDataBase::connectToDataBase() {
	int rez = sqlite3_open(ROOT_TO_DB, &db);
	if (rez != SQLITE_OK)
		throw std::runtime_error(string("Error! Can't open dataBase"));
	return (SUCCESS);
}

int SQLiteDataBase::createTable() {
	string sqlQuery = "CREATE TABLE IF NOT EXISTS USERS(" \
      "Id           INT PRIMARY KEY	NOT NULL," \
      "Name			CHAR(15)        NOT NULL," \
      "Password     CHAR(15)		NOT NULL," \
      "LocalScore2  INT				NOT NULL," \
      "LocalScore1  INT				NOT NULL);" \
      "CREATE TABLE IF NOT EXISTS LAST_SESSION(" \
      "DefaultId INT PRIMARY KEY NOT NULL," \
      "LastId INT );";
	return queryExecutor(sqlQuery);
}

int SQLiteDataBase::queryExecutor(const string& sqlQuery) {
	int rez = sqlite3_exec(db, sqlQuery.c_str(), nullptr, nullptr, nullptr);
	if (rez != SQLITE_OK)
		throw std::runtime_error(string("Error in Sql query: " + string(sqlite3_errmsg(db))));
	return SUCCESS;
}

int SQLiteDataBase::getSingle(const std::string &sqlQuery, int queryType) {
	sqlite3_stmt *stmt = nullptr;
	
	int rez = sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &stmt, nullptr);
	if (rez != SQLITE_OK)
		throw std::runtime_error(string("Error in Sql query: " + string(sqlite3_errmsg(db))));
	rez = sqlite3_step(stmt);
	if (rez != SQLITE_ROW && rez != SQLITE_DONE) {
		sqlite3_finalize(stmt);
		throw std::runtime_error(sqlite3_errmsg(db));
	}
	if (rez == SQLITE_DONE) {// не нашли пользователя
		if (status == USER_BEEN_LOGGED) {
			std::get<Id>(selectResult) = -1;
			std::get<Name>(selectResult) = "null";
			std::get<Password>(selectResult) = "null";
			std::get<LocalScore1>(selectResult) = -1;
			std::get<LocalScore2>(selectResult) = -1;
		}
		sqlite3_finalize(stmt);
		return USER_NOT_FOUND;
	}
	if (queryType == FILL) {
		std::get<Id>(selectResult) = sqlite3_column_int(stmt, Id);
		std::get<Name>(selectResult) = (char *) sqlite3_column_text(stmt, Name);
		std::get<Password>(selectResult) = (char *) sqlite3_column_text(stmt, Password);
		std::get<LocalScore1>(selectResult) = sqlite3_column_int(stmt, LocalScore1);
		std::get<LocalScore2>(selectResult) = sqlite3_column_int(stmt, LocalScore2);
	}
	sqlite3_finalize(stmt);
	return SUCCESS;
}