#include "logic/Game.h"


Game::Game() {}

Game::~Game() {}

short Game::menu() {
    //Тут вызывается графическая менюшка(возвращает 0 для клиента или 1 для сервера), но пока что это все работает через консоль
    //Делать менюшку в другом окне, а потом ззакрывать его и открывать оновное окно?
    //Если выбран сервер, то окно в л.с. закрывается т.к. для сервера окно не нужно
    std::cout << "Напишите:\n2 - для запуска клиента\n3 - для запуска сервера\n4 - для выхода";
    short gameMode = 4;
    std::cin >> gameMode;
    return gameMode;

}

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
