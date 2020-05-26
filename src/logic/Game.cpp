#include "logic/Game.h"

Game::Game() {}

Game::~Game() {}

//void Game::exitGame() {}

size_t Game::loginMenu(sp_t<Window> window, SQLiteDataBase& myDB) {

    static string type = "login";  //зачем static??????????????????????????????

    pair<pair<string, string>, string> user;  //<<nickname, password>, login/registration>

    user.second = type;

    string errorAuth;  //ошибка логина/регистрации

    bool success = false;

    while (!success) {  // add try-catch??

        user = displayLoginMenu(window->getRenderWindow(), type, errorAuth);  //внутри крутится цикл с отрисовкой меню

        //проверка логина/регистрации, либо выход из игры
        if (user.second == "login") {
            if (myDB.getAuthorizeUser(user.first.first, user.first.second) != USER_NOT_FOUND) {
                success = true;
            } else {
                errorAuth = "user not found";
            }
        } else if (user.second == "registration") {
            if (myDB.setUser(user.first.first, user.first.second) == SUCCESS) {
                type = "login";
                errorAuth = "";
            } else {
                errorAuth = "user already exist";
            }

        } else if (user.second == "exit") {
//                type = "exit";  //тут можно просто закрыть окно и завершить программу??????????????????????
//                success = true;
//            window->close();
            return 0;
        }
    }
    return 1;
}

void  Game::play() {

    sp_t<Window> window(new Window);

    window->createRenderWindow(window, screenWidth, screenHeight, "Menu");

    SQLiteDataBase myDB;

    size_t nextStep = loginMenu(window, myDB);

    auto score5 = myDB.getStandings(5);

    //1 - начало гонки, 2 - главное меню, 0 - выход из игры
    while (true) {

        switch (nextStep) {
            case 1:
                std::cout << "Запуск игры\n";
                myGameState = std::make_shared<GameState>(window);
                nextStep = myGameState->gameLoop();
                break;
            case 2:
                nextStep = displayMenu(window->getRenderWindow(), myDB.getUserNickname(), score5);
                break;
            case 0:
                std::cout << "Выход\n";
                window->close();
                return;
                break;
            default:
                std::cout << "В nextStep что-то не то\n";
                window->close();
                return;
                break;
        }
    }
}

//
//        switch (displayMenu(window->getRenderWindow(), myDB.getUserNickname(), score5)) {
//            case 1:
//                std::cout << "Запуск игры\n";
//
//                myGameState = std::make_shared<GameState>(window);
//                nextStep = myGameState->gameLoop();
//                break;
//            case 0:
//                std::cout << "Выход\n";
//                window->close();
//                break;
//            default:
//                std::cout << "Нажато что-то не то\n";
//                window->close();
//                break;
//        }
//
//
//        window->close();
//

