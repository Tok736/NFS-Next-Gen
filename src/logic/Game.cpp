#include <physics/SQLite.h>
#include "logic/Game.h"

enum typeForm{
    login = 1,
    registration = 2,
};

Game::Game() {}

Game::~Game() {}

//void Game::exitGame() {}


void  Game::playGame() {

    sp_t<Window> window(new Window);
    window->createRenderWindow(window, screenWidth, screenHeight, "Menu");


    SQLiteDataBase db;
    static string type = "login";
    pair<pair<string, string>, string> user;
    user.second = type;

	/*
    bool success = false;
    while (!success)
    {
        user = displayLoginMenu(window->getRenderWindow(),type);
        if (user.second == "login" && db.getAuthorizeUser(user.first.first, user.first.second) != USER_NOT_FOUND)
            success = true;
        else if (user.second == "registration" && db.setUser(user.first.first, user.first.second) == SUCCESS)
            type = "login";
        else if (user.second == "exit") {
            type = "exit";
            success = true;
        }
    }*/

    if (type != "exit")
        switch (displayMenu(window->getRenderWindow(), db.getUserNickname())) {
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
    else{
        window->close();

    }
}
