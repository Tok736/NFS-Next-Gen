#ifndef PHYSICS_IDATABASE_H
#define PHYSICS_IDATABASE_H

using std::string;

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

#endif //PHYSICS_IDATABASE_H
