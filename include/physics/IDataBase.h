#ifndef PHYSICS_IDATABASE_H
#define PHYSICS_IDATABASE_H

using std::string;

class AbstractDataBase{
public:
	virtual ~AbstractDataBase();
	virtual int getAutorizeUser(string passwd) = 0;// по паролю возвращается Id, либо ошибка
	virtual string getGraphicTexture(int textureId) = 0; //возвращает путь из static для картинок
	virtual int getUserLocalScore(int userId) = 0; //возвращает очки в локальной игре
	virtual int getUserNetworkScore(int userId) = 0; //воозвращает очки в сетевой игре
	virtual string *getStandings(int topCount) = 0; // топ игроков в турнирной таблице (для сети)
	virtual string getUserNickname(int userId) = 0;// Возвращается ник пользователя
	virtual int deleteUser(int userId) = 0;
	virtual void setUser(string nickname) = 0; // регистрация нового пользователя
	virtual void setUserLocalScore(int userId) = 0; //Очки для SinglePlayer
	virtual void setUserNetworkScore(int userId) = 0; // Очки для MultiPlayer
};

#endif //PHYSICS_IDATABASE_H
