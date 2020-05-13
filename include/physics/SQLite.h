#ifndef PHYSICS_SQLITEDATABASE_H
#define PHYSICS_SQLITEDATABASE_H

#include <sqlite3.h>

class AbstractDataBase {
public:
	virtual ~AbstractDataBase() = default;
	virtual int getAutorizeUser(const string& nickName, const string& passwd) = 0;// по паролю и нику возвращается Id, либо ошибка
	virtual string getUserNickname(int userId) = 0;// Возвращается ник пользователя
	virtual int setUser(const string& nickName, const string& passwd) = 0; // регистрация нового пользователя
	virtual int deleteUser(int userId) = 0;
	virtual string getGraphicTexture(int textureId) = 0; //возвращает путь из static для картинок
	virtual int getUserLocalScore(int userId) = 0; //возвращает очки в локальной игре
	virtual int getUserNetworkScore(int userId) = 0; //воозвращает очки в сетевой игре
	virtual string *getStandings(int topCount) = 0; // топ игроков в турнирной таблице (для сети)
	virtual int setUserLocalScore(int userId, int local) = 0; //Очки для SinglePlayer
	virtual int setUserNetworkScore(int userId, int global) = 0; // Очки для MultiPlayer
};

class SQLiteDataBase{
public:
	SQLiteDataBase();
	~SQLiteDataBase();
	int getAutorizeUser(const string& nickName, const string& passwd) override;
	string getGraphicTexture(int textureId) override;
	int getUserLocalScore(int userId) override;
	int getUserNetworkScore(int userId) override;
	string *getStandings(int topCount) override;
	string getUserNickname(int userId) override;
	int deleteUser(int userId) override;
	void setUser(const string& nickName, const string& passwd) override;
	void setUserLocalScore(int userId) override;
	void setUserNetworkScore(int userId) override;
private:
	string sql;
	void setSql();
	int deleteInfo();
	int updateInfo();
	int selectInfo();
	int insertInfo();
	int createTable();
	int connectToDataBase(string path);
};

#endif //PHYSICS_SQLITEDATABASE_H
