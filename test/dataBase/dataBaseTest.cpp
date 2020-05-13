#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../include/physics/IDataBase.h"

using std::string;
using std::vector;
using std::cout;

#define usersCount 20 //количество потенциальных пользователей в БД
#define userExist 0
#define localRating 1
#define globalRating 2

class MockDataBase : public AbstractDataBase {
public:
	MOCK_METHOD2(getAutorizeUser, int(const string& nickName, const string& passwd));
	MOCK_METHOD1(getGraphicTexture, string(int textureId));
	MOCK_METHOD1(getUserLocalScore, int(int userId));
	MOCK_METHOD1(getUserNetworkScore, int(int userId));
	MOCK_METHOD1(getStandings, string*(int topCount));
	MOCK_METHOD1(getUserNickname, string(int userId));
	MOCK_METHOD1(deleteUser, int(int userId));
	MOCK_METHOD2(setUser, int(const string& nickName, const string& passwd));
	MOCK_METHOD2(setUserLocalScore, int(int userId, int local));
	MOCK_METHOD2(setUserNetworkScore, int(int userId, int global));
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

void putUsersInDataBase(MockDataBase &data, vector<string> &users, vector<string> &passwd, vector<int> &usersId) {
	
	EXPECT_CALL(data, setUser).Times(testing::AtLeast(usersCount));
	for (int i = 0; i < usersCount; ++i) { //записываем новых пользователей в БД, а в вектор результатов записи id пользователя или id ошибки
		usersId.push_back(data.setUser(users[i], passwd[i])); // Создали 20 разных пользователей c уникальным ником и паролем
	}
}

void checkFindById(MockDataBase &data, vector<string> &users, vector<int> &usersId) { // проверяем выдачу ника по id
	
	EXPECT_CALL(data, getUserNickname).Times(testing::AtLeast(usersCount));
	for (int i = 0; i < usersCount; ++i)
		ASSERT_EQ(data.getUserNickname(usersId[i]) == users[i], false);
	// пробуем поиск по несуществующему id
}

void checkDublicateUser(MockDataBase &data, vector<int> &usersId) {
	string currentUser;
	
	EXPECT_CALL(data, getUserNickname).Times(testing::AtLeast(usersCount));
	EXPECT_CALL(data, setUser).Times(testing::AtLeast(usersCount));
	for (int i = 0; i < usersCount; ++i) {
		currentUser = data.getUserNickname(usersId[i]);
		ASSERT_EQ(data.setUser(currentUser, "1"), userExist); // пытаемся зарегистрировать в бд существующего пользователя
	}
}

void checkAuthorization(MockDataBase &data, vector<string> &users, vector<string> &usersPasswds, vector<int> &usersId){ //проверяем возможность авторизации
	int currentUserId;
	
	EXPECT_CALL(data, getAutorizeUser).Times(testing::AtLeast(usersCount));
	for (int i = 0; i < usersCount; ++i) {
		currentUserId = usersId[i];
		ASSERT_EQ(data.getAutorizeUser(users[i],usersPasswds[i]), currentUserId); // Метод БД должен вернуть корректный Id, т.к. пользователи есть в БД и входные данные заведомо верны
	}
	// пробуем ввести невыерны данные
}

void checkDeleteUser(MockDataBase &data, vector<int> &usersId) {
	
	EXPECT_CALL(data, deleteUser).Times(testing::AtLeast(usersCount));
	for (int i = 0; i < usersCount; ++i) { //удаляем всех пользователей из БД
		ASSERT_EQ(data.deleteUser(usersId[i]), userExist); //  все удаления должны быть успешны
	}
	// пробуем удалить несуществующего пользователя
}

void checkUsersUpdate(MockDataBase &data, vector<int> &usersId) {
	string currentUser;
	
	EXPECT_CALL(data, setUserLocalScore).Times(testing::AtLeast(usersCount));
	EXPECT_CALL(data, setUserNetworkScore).Times(testing::AtLeast(usersCount));
	EXPECT_CALL(data, getUserLocalScore).Times(testing::AtLeast(usersCount));
	EXPECT_CALL(data, getUserNetworkScore).Times(testing::AtLeast(usersCount));
	for (int i = 0; i < usersCount; ++i) { // устанавливаем всем пользователям глобальный(globalRating) и локальный(localRating) рейтинги в виде очков
		ASSERT_EQ(data.setUserLocalScore(usersId[i], localRating), userExist);
		ASSERT_EQ(data.setUserNetworkScore(usersId[i], globalRating), userExist);
		ASSERT_EQ(data.getUserLocalScore(usersId[i]), userExist);
		ASSERT_EQ(data.getUserNetworkScore(usersId[i]), userExist);
	}
}

TEST(googleTestExample, DataBasetest) {
	MockDataBase data;
	vector<string> nickNames; //список игроков  в формате player[0-19]
	vector<string> usersPasswds; // пароли пользователей
	vector<int> usersId; // список id, соответствующих игрокам, которые возвращает метод БД
	createUsersList(nickNames, usersPasswds); //создаем пользователей для бд
	putUsersInDataBase(data,nickNames, usersPasswds, usersId);
	checkDublicateUser(data,usersId);
	checkAuthorization(data,nickNames, usersPasswds, usersId);
	checkFindById(data,nickNames, usersId);
	checkDeleteUser(data,usersId);
	checkUsersUpdate(data,usersId);
	cout << "Success\n";
}