#include "gtest/gtest.h"
#include "../../include/physics/SQLite.h"

using std::string;
using std::vector;
using std::cout;

constexpr int usersCount = 200; //количество потенциальных пользователей в БД
constexpr int localScore = 100;
constexpr int networkScore = 200;

void createUsersList(vector<string> &users, vector<string> &passwd) {
	string buf = "player";
	for (int i = 0; i < usersCount; ++i) { //формируем список из потенциальных игроков
		users.push_back(buf + std::to_string(i));
		passwd.push_back(std::to_string(i));
	}
}

class TestDataBase : public ::testing::Test {
protected:
	void SetUp() override {
		createUsersList(users, passwd);
		cout << "Data for test ready\n";
	}
	
	void TearDown() override {
		cout << "Test Success\n";
	}
	
	SQLiteDataBase db;
	vector<string> users; //список игроков  в формате player[0-19]
	vector<string> passwd; // пароли пользователей
};

TEST_F(TestDataBase, RegistrationCheck) {
	for (int i = 0; i < usersCount; ++i)  //записываем новых пользователей в БД
		ASSERT_EQ(db.setUser(users[i], passwd[i]), SUCCESS);
}

TEST_F(TestDataBase, AuthorizationCheck) {
	for (int i = 0; i < usersCount; ++i)
		ASSERT_EQ(db.getAuthorizeUser(users[i], "default wrong password"), USER_NOT_FOUND);
	for (int i = 0; i < usersCount; ++i)
		ASSERT_EQ(db.getAuthorizeUser(users[i], passwd[i]), i + 1);
}

TEST_F(TestDataBase, DuplicationTabuCheck) {
	for (int i = 0; i < usersCount; ++i)
		ASSERT_EQ(db.setUser(users[i], "random"), USER_ALREADY_EXISTS); // пытаемся зарегистрировать в бд существующего пользователя
}

TEST_F(TestDataBase, FindCheck) {
	for (int i = 0; i < usersCount; ++i) {
		db.getAuthorizeUser(users[i], passwd[i]);
		ASSERT_TRUE(db.getUserNickname() == users[i]);
	}
}

TEST_F(TestDataBase, UsersUpdateCheck) {
	for (int i = 0; i < usersCount; ++i) { // устанавливаем всем пользователям  рейтинги в виде очков, проверяем обновления
		db.getAuthorizeUser(users[i], passwd[i]);
		ASSERT_EQ(db.setUserLocalScore(localScore), SUCCESS);
		ASSERT_EQ(db.setUserNetworkScore(networkScore), SUCCESS);
		ASSERT_EQ(db.getUserLocalScore(), localScore);
		ASSERT_EQ(db.getUserNetworkScore(), networkScore);
	}
}

TEST_F(TestDataBase, CorrectLastSessionCheck) {
	ASSERT_EQ(db.getLastSession(), USER_NOT_FOUND); // Не было установки (галочки) для сохранения сессии
	for (int i = 0; i < usersCount - 1; ++i) { // устанавливаем всем пользователям  рейтинги в виде очков, проверяем обновления
		db.getAuthorizeUser(users[i], passwd[i]);
		ASSERT_EQ(db.setLastSession(), SUCCESS); // Сохраняем сессию текущего авторизованного пользователя
		db.getAuthorizeUser(users[i + 1], passwd[i + 1]); // Заходим под другим пользователем
		ASSERT_EQ(db.getLastSession(), SUCCESS); // Открываем сессию предыдущего пользователя
		ASSERT_EQ(db.getUserNickname(), users[i]); //  Проверяем, что доступна сохраненная сессия
	}
}

TEST_F(TestDataBase, DeleteUsersCheck) {
	for (int i = 0; i < usersCount; ++i) {//удаляем всех пользователей из БД
		db.getAuthorizeUser(users[i], passwd[i]);
		ASSERT_EQ(db.deleteUser(), SUCCESS); //  все удаления должны быть успешны для авторизованных пользователей
	}
}