#include "logic/ClientState.h"
ClientState::ClientState() {
    myWindow = std::make_shared<Window>();
    myServerState = std::make_shared<ServerState>();
}

//версия для варианта без сети (серверная часть внутри клиентской):
ClientState::ClientState(sp_t<Window> wndPtr, sp_t<ServerState> srvrStPtr) : myWindow(wndPtr), myServerState(srvrStPtr) {
}


ClientState::~ClientState() {}

void ClientState::clientLoop() {
    Clock clock;
    vector<int> actions;
    int action;
    myServerState->gamePreparation();  //пока нет сети, серверная часть туть

    actualElements.push_back(std::make_shared<Obstruction>(0, 0, 0));
    actualElements.push_back(std::make_shared<Obstruction>(1, 0, 0));
    for (int i = 10; i <=18; ++i) {
        actualElements.push_back(std::make_shared<Obstruction>(i, 0, 0));
    }

    myWindow->createTextures(actualElements);


    while (myWindow->isOpen()) {
    	usleep(9000);
        int freq = (int)clock.getClockSec() + 10;
        myWindow->handleEvents(actions);
        if (!actions.empty() && actions[0] == endOfTheGame)
            myWindow->close();
        else if (!actions.empty() && actions[0] == pauseOfTheGame)
        {
            actions.pop_back();
            if (!pauseWindow(myWindow, freq))
                return;
        }
        else {
            if (!actions.empty())
                action = actions[0];
            else
                action = myNoAction;
            myServerState->myCollision.setFreq(freq);
            myServerState->myCollision.setAction(myServerState->myMap, myServerState->players, actions);
        }
        myServerState->composeActualElements(actualElements);
        myWindow->render(actualElements, action, freq);
        myWindow->display();
    }
}

