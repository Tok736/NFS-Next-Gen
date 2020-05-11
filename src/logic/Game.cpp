#include "logic/Game.h"


Game::Game() {}

Game::~Game() {}

bool Game::menu() {
    //Тут вызывается графическая менюшка(возвращает 0 для клиента или 1 для сервера), но пока что это все работает через консоль
    //Делать менюшку в другом окне, а потом ззакрывать его и открывать оновное окно?
    //Если выбран сервер, то окно в л.с. закрывается т.к. для сервера окно не нужно
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
