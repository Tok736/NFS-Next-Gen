#include <physics/SQLite.h>
#include "logic/Game.h"

enum typeForm{
    login = 1,
    registration = 2,
};

Game::Game() {}

Game::~Game() {}

//void Game::exitGame() {}

void checkLogin(SQLiteDataBase &db, pair<pair<string, string>, string> &user, string &type)
{
    while (type == "login" && db.getAuthorizeUser(user.first.first, user.first.second) == USER_NOT_FOUND)
    {
        user = displayLoginMenu(type);
    }
}

void  Game::playGame() {

    sp_t<Window> window(new Window);


    SQLiteDataBase db;
    static string type = "login";
    pair<pair<string, string>, string> user;
    user.second = type;

//    user = displayLoginMenu(type);

    checkLogin(db, user, type);
    while (type == "registration")
    {
        user = displayLoginMenu(type);
        if (db.setUser(user.first.first, user.first.second) == SUCCESS) {
            checkLogin(db, user, type);
        }
    } //повторный ввод - для регистрации


    switch (displayMenu(window, db.getUserNickname())) {
        case 1:
            std::cout << "Запуск клиента\n";

            myClientState = std::make_shared<ClientState>(window, std::make_shared<ServerState>());
            myClientState->clientLoop();
            break;
        case 2:
            std::cout << "Запуск сервера\n";
            window->close();
            break;
        case 0:
            std::cout << "Выход\n";
            window->close();
            break;
        default:
            std::cout << "Нажато что-то не то\n";
            window->close();
            break;
    }
}
