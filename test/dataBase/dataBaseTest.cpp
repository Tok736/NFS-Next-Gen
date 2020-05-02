#include "gtest/gtest.h"
#include "../include/physics/IDataBase.h"

using std::string;
using std::vector;
using std::cout;

#define usersCount 20 //количество потенциальных пользователей в БД
#define userExist -1

class MockDataBase : public AbstractDataBase {
public:
	int getAutorizeUser(const string& nickName, const string& passwd) override {return -1;}
	string getUserNickname(int id) override {return "nun";}
	int setUser(const string& nickname, const string& passwd) override {return -1;}
	int deleteUser(int userId) override {return 1;}
	//MOCK_METHOD0(getAutorizeUser, int());
	/*MOCK_METHOD0(getGraphicTexture, string());
	MOCK_METHOD0(getUserLocalScore, int());
	MOCK_METHOD0(getUserNetworkScore, int());
	MOCK_METHOD0(getStandings, string*());
	MOCK_METHOD0(getUserNickname, string());
	MOCK_METHOD0(deleteUser, int());
	MOCK_METHOD0(setUser, int());
	MOCK_METHOD0(setUserLocalScore, int());
	MOCK_METHOD0(setUserNetworkScore, int());*/
};

string itoa(int nb) {
	int len = 0;
	int buf = nb;
	
	if (buf < 0) // номер игрока неотрицательное число!
		assert(false);
	while (nb) {
		nb /= 10;
		++len;
	}
	if (!len)
		len = 1;
	string conversion(len, '0');
	for(int i = len - 1; i >= 0; --i) {
		conversion[i] = buf % 10 + '0';
		buf /= 10;
	}
	return conversion;
}

void createUsersList(vector<string> &users, vector<string> &passwd) {
	string buf = "player";
	for (int i = 0; i < usersCount; ++i) { //формируем список из потенциальных игроков
		users.push_back(buf + itoa(i));
		passwd.push_back(itoa(i));
	}
}

class dataBaseUser {
public:
	explicit dataBaseUser(AbstractDataBase* dataBase) : dataBase_(dataBase){};
	
	bool Authorize(const string &nickName, const string &passwd) {
		dataBase_->getAutorizeUser(nickName, passwd);
		return true;
	}
	AbstractDataBase *dataBase_;
};


void putUsersInDataBase(vector<string> &users, vector<string> &passwd, vector<int> &usersId) {
	MockDataBase data;
	
	for (int i = 0; i < usersCount; ++i) { //записываем новых пользователей в БД, а в вектор результатов записи id пользователя или id ошибки
		usersId.push_back(data.setUser(users[i], passwd[i])); // Создали 20 разных пользователей c уникальным ником и паролем
	}
}

void checkFindById(vector<string> &users, vector<int> &usersId) { // проверяем выдачу ника по id
	MockDataBase data;
	for (int i = 0; i < usersCount; ++i)
		ASSERT_EQ(data.getUserNickname(usersId[i]) == users[i], false);
	// пробуем поиск по несуществующему id
}

void checkDublicateUser(vector<int> &usersId) {
	MockDataBase data;
	string currentUser;
	
	for (int i = 0; i < usersCount; ++i) {
		currentUser = data.getUserNickname(usersId[i]);
		ASSERT_EQ(data.setUser(currentUser, "1"), userExist); // пытаемся зарегистрировать в бд существующего пользователя
	}
}

void checkAuthorization(vector<string> &users, vector<string> &usersPasswds, vector<int> &usersId){ //проверяем возможность авторизации
	MockDataBase data;
	int currentUserId;
	for (int i = 0; i < usersCount; ++i) {
		currentUserId = usersId[i];
		ASSERT_EQ(data.getAutorizeUser(users[i],usersPasswds[i]), currentUserId); // Метод БД должен вернуть корректный Id, т.к. пользователи есть в БД и входные данные заведомо верны
	}
	// пробуем ввести невыерны данные
}

void checkDeleteUser(vector<int> &usersId) {
	MockDataBase data;
	
	for (int i = 0; i < usersCount; ++i) { //удаляем всех пользователей из БД
		ASSERT_EQ(data.deleteUser(usersId[i]), 1); //  все удаления должны быть успешны
	}
	// пробуем удалить несуществующего пользователя
}


TEST(googleTestExample, DataBasetest) {
	vector<string> nickNames; //список игроков  в формате player[0-19]
	vector<string> usersPasswds; // пароли пользователей
	vector<int> usersId; // список id, соответствующих игрокам, которые возвращает метод БД
	createUsersList(nickNames, usersPasswds);
	putUsersInDataBase(nickNames, usersPasswds, usersId);
	
	checkDublicateUser(usersId);
	checkAuthorization(nickNames, usersPasswds, usersId);
	checkFindById(nickNames, usersId);
}