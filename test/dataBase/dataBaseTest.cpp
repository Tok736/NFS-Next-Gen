#include "gtest/gtest.h"
#include "../../include/physics/SQLite.h"

constexpr int usersCount = 200; //количество потенциальных пользователей в БД
constexpr int localScore = 100;
constexpr int networkScore = 200;

void createUsersList(vector<string> &users, vector<string> &passwd) {
	string buf = "player";
	for (int i = 0; i < usersCount; ++i) { //формируем список из потенциальных игроков
		users.push_back(buf + std::toString(i));
		passwd.push_back(std::toString(i));
	}
}

void putUsersInDataBase(SQLiteDataBase &db, vector<string> &users, vector<string> &passwd) {
	for (int i = 0; i < usersCount; ++i)  //записываем новых пользователей в БД
		ASSERT_EQ(db.setUser(users[i], passwd[i]), SUCCESS);
}

void checkFind(SQLiteDataBase &db, vector<string> &users, vector<string> &passwd) { // проверяем выдачу ника
	for (int i = 0; i < usersCount; ++i) {
		db.getAuthorizeUser(users[i], passwd[i]);
		ASSERT_EQ(db.getUserNickname() == users[i], true);
	}
}

void checkDuplicateUser(SQLiteDataBase &db, vector<string> &users) {
	for (int i = 0; i < usersCount; ++i)
		ASSERT_EQ(db.setUser(users[i], "random"),
				  USER_ALREADY_EXISTS); // пытаемся зарегистрировать в бд существующего пользователя
}

void checkAuthorization(SQLiteDataBase &db, vector<string> &users, vector<string> &passwd) { //проверяем возможность авторизации
	for (int i = 0; i < usersCount; ++i)
		ASSERT_EQ(db.getAuthorizeUser(users[i], "default wrong password"), USER_NOT_FOUND);
	for (int i = 0; i < usersCount; ++i)
		ASSERT_EQ(db.getAuthorizeUser(users[i], passwd[i]), i + 1);
}

void checkDeleteUser(SQLiteDataBase &db, vector<string> &users, vector<string> &passwd) {
	for (int i = 0; i < usersCount; ++i) {//удаляем всех пользователей из БД
		db.getAuthorizeUser(users[i], passwd[i]);
		ASSERT_EQ(db.deleteUser(), SUCCESS); //  все удаления должны быть успешны для авторизованных пользователей
	}
}

void checkUsersUpdate(SQLiteDataBase &db, vector<string> &users, vector<string> &passwd) {
	for (int i = 0;
		 i < usersCount; ++i) { // устанавливаем всем пользователям  рейтинги в виде очков, проверяем обновления
		db.getAuthorizeUser(users[i], passwd[i]);
		ASSERT_EQ(db.setUserLocalScore(localScore), SUCCESS);
		ASSERT_EQ(db.setUserNetworkScore(networkScore), SUCCESS);
		ASSERT_EQ(db.getUserLocalScore(), localScore);
		ASSERT_EQ(db.getUserNetworkScore(), networkScore);
	}
}

TEST(googleTestExample, DataBasetest) {
	SQLiteDataBase db;
	vector<string> nickNames; //список игроков  в формате player[0-19]
	vector<string> usersPasswds; // пароли пользователей
	
	createUsersList(nickNames, usersPasswds);
	putUsersInDataBase(db,nickNames, usersPasswds);
	checkAuthorization(db, nickNames, usersPasswds);
	checkDuplicateUser(db, nickNames);
	checkFind(db, nickNames, usersPasswds);
	checkUsersUpdate(db, nickNames, usersPasswds);
	checkDeleteUser(db,nickNames, usersPasswds);
	putUsersInDataBase(db,nickNames, usersPasswds);
	checkDeleteUser(db,nickNames, usersPasswds);
	db.getStandings(20);
	cout << "Success DataBaseTest\n";
}