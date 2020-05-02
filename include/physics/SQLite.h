#ifndef PHYSICS_SQLITEDATABASE_H
#define PHYSICS_SQLITEDATABASE_H

#include "IDataBase.h"
#include <sqlite3.h>

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
