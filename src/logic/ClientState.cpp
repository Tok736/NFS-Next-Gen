#include "logic/ClientState.h"


ClientState::ClientState() {
    myWindow = std::make_shared<Window>();
//    myEvent = new MockEvent;
//    myClient = new MockClient;
//    myDB = new MockAbstractDataBase;
    myServerState = std::make_shared<ServerState>();
}


//версия для варианта без сети (серверная часть внутри клиентской):
ClientState::ClientState(sp_t<Window> wndPtr, sp_t<ServerState> srvrStPtr) : myWindow(wndPtr), myServerState(srvrStPtr) {
//    myEvent = new MockEvent;
//    myClient = new MockClient;
//    myDB = new MockAbstractDataBase;
}

//ClientState::ClientState(sp_t<Window> wndPtr) : myWindow(wndPtr) {
//    myEvent = new MockEvent;
//    myClient = new MockClient;
//    myDB = new MockAbstractDataBase;
//}
//
//ClientState::ClientState(Event* evntPtr) : myEvent(evntPtr) {
//    myWindow = std::make_shared<Window>();
//    myClient = new MockClient;
//    myDB = new MockAbstractDataBase;
//}
//
//ClientState::ClientState(Client* clntPtr) : myClient(clntPtr) {
//    myWindow = std::make_shared<Window>();
//    myEvent = new MockEvent;
//    myDB = new MockAbstractDataBase;
//}
//
//ClientState::ClientState(AbstractDataBase* dbPtr) : myDB(dbPtr) {
//    myWindow = std::make_shared<Window>();
//    myEvent = new MockEvent;
//    myClient = new MockClient;
//}
//
//ClientState::ClientState(sp_t<Window> wndPtr, Event* evntPtr, Client* clntPtr, AbstractDataBase* dbPtr)
//        : myWindow(wndPtr), myEvent(evntPtr), myClient(clntPtr), myDB(dbPtr) {
//
//}

ClientState::~ClientState() {}

//ClientState::ClientState(char* hostIp, char* playerName) {
//    myClient.run(hostIp, playerName);
//}

//void ClientState::clientPreparation() {
//
////    float width = 580;
////    float height = 600;d
//    std::string nickname, password;
////    std::cin >> nickname;
////    std::cin >> password;
//    int myId;
//    myId = myDB->getAutorizeUser(nickname, password);
//
//    myClient->sendName(myDB->getUserNickname(myId));
//    myWindow->createRenderWindow(/*myWindow, width, height, "game"*/);
//
//}

void ClientState::clientLoop() {
//    while (true) {
//        myEvent->getEvent();
//        myClient->send(/*myEvent*/);
//        actualElements = myClient->get();
//        myWindow->render(/*actualElements*/);
//        break;
//    }

    Clock clock;
    vector<int> actions;
    int action;
    myServerState->gamePreparation();  //пока нет сети, серверная часть туть

    myServerState->composeActualElements(actualElements);


    myWindow->createTextures(actualElements);


    while (myWindow->isOpen()) {
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

//        for(vector<Obstruction>::iterator it=myServerState->myMap.begin() + 2; it!=myServerState->myMap.end(); ++it){
//            it->setY(it->getY() + 1);
//        }
    }
}

//void ClientState::exit() {
//    myDB->getExperience();
//    myWindow->close();
//}