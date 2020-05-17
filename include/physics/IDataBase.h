#ifndef PHYSICS_IDATABASE_H
#define PHYSICS_IDATABASE_H
#include <string>
#include <vector>
#include <memory>
#include <iostream>

using std::cout;
using std::string;
using std::vector;


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
};

#endif //PHYSICS_IDATABASE_H
