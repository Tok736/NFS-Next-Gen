#include "logic/ClientState.h"


ClientState::ClientState() {
    myWindow = new MockWindow;
    myEvent = new MockEvent;
    myClient = new MockClient;
    myDB = new MockAbstractDataBase;
}

ClientState::ClientState(Window* wndPtr) : myWindow(wndPtr) {
    myEvent = new MockEvent;
    myClient = new MockClient;
    myDB = new MockAbstractDataBase;
}

ClientState::ClientState(Event* evntPtr) : myEvent(evntPtr) {
    myWindow = new MockWindow;
    myClient = new MockClient;
    myDB = new MockAbstractDataBase;
}

ClientState::ClientState(Client* clntPtr) : myClient(clntPtr) {
    myWindow = new MockWindow;
    myEvent = new MockEvent;
    myDB = new MockAbstractDataBase;
}

ClientState::ClientState(AbstractDataBase* dbPtr) : myDB(dbPtr) {
    myWindow = new MockWindow;
    myEvent = new MockEvent;
    myClient = new MockClient;
}

ClientState::ClientState(Window* wndPtr, Event* evntPtr, Client* clntPtr, AbstractDataBase* dbPtr)
        : myWindow(wndPtr), myEvent(evntPtr), myClient(clntPtr), myDB(dbPtr) {

}

ClientState::~ClientState() {

}

//ClientState::ClientState(char* hostIp, char* playerName) {
//    myClient.run(hostIp, playerName);
//}

void ClientState::clientPreparation() {

//    float width = 580;
//    float height = 600;d
    std::string nickname, password;
//    std::cin >> nickname;
//    std::cin >> password;
    int myId;
    myId = myDB->getAutorizeUser(nickname, password);

    myClient->sendName(myDB->getUserNickname(myId));
    myWindow->createRenderWindow(/*myWindow, width, height, "game"*/);

}

void ClientState::clientLoop() {  //добавитьобработку времени
    while (true) {
        myEvent->getEvent();
        myClient->send(/*myEvent*/);
        actualElements = myClient->get();
        myWindow->render(/*actualElements*/);
        break;
    }
}

void ClientState::exit() {
    myDB->getExperience();
    myWindow->close();
}