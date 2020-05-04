#include "logic/ClientState.h"


ClientState::ClientState() {
    myWindow = new MockWindow;
    myEvent = new MockEvent;
    myClient = new MockClient;
}

ClientState::ClientState(Window* wndPtr) : myWindow(wndPtr) {
    myEvent = new MockEvent;
    myClient = new MockClient;
}

ClientState::ClientState(Event* evntPtr) : myEvent(evntPtr) {
    myWindow = new MockWindow;
    myClient = new MockClient;
}

ClientState::ClientState(Client* clntPtr) : myClient(clntPtr) {
    myWindow = new MockWindow;
    myEvent = new MockEvent;
}

ClientState::ClientState(Window* wndPtr, Event* evntPtr, Client* clntPtr)
        : myWindow(wndPtr), myEvent(evntPtr), myClient(clntPtr) {

}

ClientState::~ClientState() {

}

//ClientState::ClientState(char* hostIp, char* playerName) {
//    myClient.run(hostIp, playerName);
//}

void ClientState::clientLoop() {  //добавитьобработку времени
    float width = 580;
    float height = 600;
    myClient->sendName(/**/);
    myWindow->createRenderWindow(/*myWindow, width, height, "game"*/);
    while (true) {
        myEvent->getEvent();
        myClient->send(/*myEvent*/);
        actualElements = myClient->get();
        myWindow->render(/*actualElements*/);
        break;
    }
    exit();
}

void ClientState::exit() {
    myWindow->close();
}