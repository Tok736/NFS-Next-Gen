#include "logic/Game.h"


Game::Game() {}

Game::~Game() {}

bool Game::menu() {
    std::cout << "Напишите:\n0 - для запуска клиента\n1 - для запуска сервера\n";
    bool gameMode = 0;
    std::cin >> gameMode;
    return gameMode;
}

//void Game::exitGame() {}

void  Game::playGame() {
    switch (menu()) {
        case 0:
            std::cout << "Запуск клиента\n";
            myClientState = std::make_shared<ClientState>();
            myClientState->clientPreparation();
            myClientState->clientLoop();
            myClientState->exit();
            break;
        case 1:
            std::cout << "Запуск сервера\n";
            myServerState = std::make_shared<ServerState>();
            myServerState->gamePreparation();
            myServerState->serverLoop();
            myServerState->exit();
            break;
    }
}
