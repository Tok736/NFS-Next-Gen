#ifndef PHYSICS_SQLITEDATABASE_H
#define PHYSICS_SQLITEDATABASE_H
#include <sqlite3.h>
#include <string>
#include <vector>
#include <memory>
#include <iostream>

constexpr char	ROOT_TO_DB[] = "dataBase/UserData.db";
enum DB_STATUS { USER_ALREADY_EXISTS = -2, USER_NOT_FOUND = -1, SUCCESS = 0, USER_BEEN_LOGGED = 1 };
enum DB_RETURN { Id = 0, Name = 1, Password = 2, LocalScore1 = 3, LocalScore2 = 4};
constexpr int 	FILL = 2;
constexpr int	SEARCH = 3;

class AbstractDataBase {
public:
	virtual ~AbstractDataBase() = default;
	virtual int getAuthorizeUser(const std::string& nickName, const std::string& passwd) = 0;// по паролю и нику возвращается Id, либо ошибка
	virtual const std::string &getUserNickname() = 0;// Возвращается ник пользователя
	virtual int setUser(const std::string& nickName, const std::string& passwd) = 0; // регистрация нового пользователя
	virtual int deleteUser() = 0;
	virtual int getUserLocalScore() = 0; //возвращает очки в локальной игре
	virtual int getUserNetworkScore() = 0; //воозвращает очки в сетевой игре
	virtual const std::tuple<std::vector<std::string>, std::vector<int>, std::vector<int>>& getStandings(int topCount) = 0; // топ игроков в турнирной таблице (для сети)
	virtual int setUserLocalScore(int local) = 0; //Очки для SinglePlayer
	virtual int setUserNetworkScore(int global) = 0; // Очки для MultiPlayer
	virtual int getLastSession() = 0; // Возврат последнего сохраненного пользователя
	virtual int setLastSession() = 0; // Сохранение последнего авторизованного пользователя(обновляется при указании сохранения или авторизации по паролю нового пользователя)
};

class SQLiteDataBase : AbstractDataBase {
public:
	SQLiteDataBase();
	~SQLiteDataBase() override;
	int getAuthorizeUser(const std::string &nickName, const std::string &passwd) override;
	const std::tuple<std::vector<std::string>, std::vector<int>, std::vector<int>> &getStandings(int topCount) override;
	const std::string &getUserNickname() override;
	int deleteUser() override;
	int setUser(const std::string &nickName, const std::string &passwd) override;
	int setUserLocalScore(int local) override;
	int setUserNetworkScore(int global) override;
	int getUserLocalScore() override;
	int getUserNetworkScore() override;
	int getLastSession()  override;
	int setLastSession() override;
	int getUserId();

private:
	int status;
	std::tuple<int, std::string, std::string, int, int> selectResult;
	std::tuple<std::vector<std::string>, std::vector<int>, std::vector<int>> topTable;
	sqlite3 *db;
private:
	int getSingle(const std::string& sqlQuery, int queryType);
	int queryExecutor(const std::string& sqlQuery);
	int createTable();
	int connectToDataBase();
};
#endif //PHYSICS_SQLITEDATABASE_H
