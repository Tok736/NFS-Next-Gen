#ifndef PHYSICS_SQLITEDATABASE_H
#define PHYSICS_SQLITEDATABASE_H
#include <sqlite3.h>
#include <string>
#include <vector>
#include <memory>
#include <iostream>

using std::cout;
using std::string;
using std::vector;

constexpr int USER_ALREADY_EXISTS = -2;
constexpr int USER_NOT_FOUND = -1;
constexpr int SUCCESS = 0;
constexpr int USER_BEEN_LOGGED = 1;

class AbstractDataBase {
public:
	virtual ~AbstractDataBase() = default;
	virtual int getAuthorizeUser(const string& nickName, const string& passwd) = 0;// по паролю и нику возвращается Id, либо ошибка
	virtual const string &getUserNickname() = 0;// Возвращается ник пользователя
	virtual int setUser(const string& nickName, const string& passwd) = 0; // регистрация нового пользователя
	virtual int deleteUser() = 0;
	virtual int getUserLocalScore() = 0; //возвращает очки в локальной игре
	virtual int getUserNetworkScore() = 0; //воозвращает очки в сетевой игре
	virtual const std::tuple<vector<string>, vector<int>, vector<int>>& getStandings(int topCount) = 0; // топ игроков в турнирной таблице (для сети)
	virtual int setUserLocalScore(int local) = 0; //Очки для SinglePlayer
	virtual int setUserNetworkScore(int global) = 0; // Очки для MultiPlayer
	virtual int getLastSession() = 0; // Возврат последнего сохраненного пользователя
	virtual int setLastSession() = 0; // Сохранение последнего авторизованного пользователя(обновляется при указании сохранения или авторизации по паролю нового пользователя)
};

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
	int getLastSession()  override;
	int setLastSession() override;
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
