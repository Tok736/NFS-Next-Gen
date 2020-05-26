//#include "logic/ClientState.h"
//
//ClientState::ClientState() {
//	myWindow = std::make_shared<Window>();
////    myEvent = new MockEvent;
////    myClient = new MockClient;
////    myDB = new MockAbstractDataBase;
//	myServerState = std::make_shared<ServerState>();
//}
//
//
////версия для варианта без сети (серверная часть внутри клиентской):
//ClientState::ClientState(sp_t<Window> wndPtr, sp_t<ServerState> srvrStPtr) : myWindow(wndPtr),
//																			 myServerState(srvrStPtr) {
////    myEvent = new MockEvent;
////    myClient = new MockClient;
////    myDB = new MockAbstractDataBase;
//}
//
////ClientState::ClientState(sp_t<Window> wndPtr) : myWindow(wndPtr) {
////    myEvent = new MockEvent;
////    myClient = new MockClient;
////    myDB = new MockAbstractDataBase;
////}
////
////ClientState::ClientState(Event* evntPtr) : myEvent(evntPtr) {
////    myWindow = std::make_shared<Window>();
////    myClient = new MockClient;
////    myDB = new MockAbstractDataBase;
////}
////
////ClientState::ClientState(Client* clntPtr) : myClient(clntPtr) {
////    myWindow = std::make_shared<Window>();
////    myEvent = new MockEvent;
////    myDB = new MockAbstractDataBase;
////}
////
////ClientState::ClientState(AbstractDataBase* dbPtr) : myDB(dbPtr) {
////    myWindow = std::make_shared<Window>();
////    myEvent = new MockEvent;
////    myClient = new MockClient;
////}
////
////ClientState::ClientState(sp_t<Window> wndPtr, Event* evntPtr, Client* clntPtr, AbstractDataBase* dbPtr)
////        : myWindow(wndPtr), myEvent(evntPtr), myClient(clntPtr), myDB(dbPtr) {
////
////}
//
//ClientState::~ClientState() {}
//
////ClientState::ClientState(char* hostIp, char* playerName) {
////    myClient.run(hostIp, playerName);
////}
//
////void ClientState::clientPreparation() {
////
//////    float width = 580;
//////    float height = 600;d
////    std::string nickname, password;
//////    std::cin >> nickname;
//////    std::cin >> password;
////    int myId;
////    myId = myDB->getAutorizeUser(nickname, password);
////
////    myClient->sendName(myDB->getUserNickname(myId));
////    myWindow->createRenderWindow(/*myWindow, width, height, "game"*/);
////
////}
//
//void ClientState::clientLoop() {
////    while (true) {
////        myEvent->getEvent();
////        myClient->send(/*myEvent*/);
////        actualElements = myClient->get();
////        myWindow->render(/*actualElements*/);
////        break;
////    }
//
//	Clock clock;
//	vector<int> actions;
//	int action;
//	myServerState->gamePreparation();  //пока нет сети, серверная часть туть
//
//	actualElements.push_back(std::make_shared<Obstruction>(0, 0, 0));
//	actualElements.push_back(std::make_shared<Car>(1, 0, 0, 0));
//	actualElements.push_back(std::make_shared<Car>(2, 0, 0, 0));
//	for (int i = 10; i <= 18; ++i) {
//		actualElements.push_back(std::make_shared<Obstruction>(i, 0, 0));
//	}
//
//	myWindow->createTextures(actualElements);
//
////    myServerState->composeActualElements(actualElements);
//	float freq;
//	int time;
//
//
//	while (myWindow->isOpen()) {
//
//		freq = clock.getClockSec();
//		time = clock.getClockSec();
//		myWindow->handleEvents(actions);
//		if (!actions.empty() && actions[0] == endOfTheGame)
//			myWindow->close();
//		else if (!actions.empty() && actions[0] == pauseOfTheGame) {
//			actions.pop_back();
//			if (!pauseWindow(myWindow->getRenderWindow(), freq))  // тут возвращается 1 - продолжить, 2 - заново, 0 - выход
//				return;
//		} else {
//			if (!actions.empty())
//				action = actions[0];
//			else
//				action = myNoAction;
//			myServerState->myCollision.setTime(time);
//			myServerState->myCollision.setAction(myServerState->myMap, myServerState->players, actions);
//		}
//		myServerState->composeActualElements(actualElements);
//		int ffreq = (int) freq;
//		myWindow->render(actualElements, action, ffreq);
//		myWindow->display();
//		usleep(16000); // 50 fps, если считать, что все исполняется в пределах 40 мс
//	}
//}
//
////void ClientState::exit() {
////    myDB->getExperience();
////    myWindow->close();
////}