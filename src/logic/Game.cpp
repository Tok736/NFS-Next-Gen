#include "logic/Game.h"


Game::Game() {}

Game::~Game() {}

//void Game::exitGame() {}

void  Game::playGame() {

    sp_t<Window> window(new Window);

    switch (displayMenu(window)) {
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
