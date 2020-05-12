#include "ServerState.h"

ServerState::ServerState(int difficulty) {
//    myHost = new MockHost;
    myCollision = Collision();
    MapGenerator myGen(difficulty);
    myMap = myGen.getVector();
}

//ServerState::ServerState(Host* hstPtr, int difficulty) : myHost(hstPtr) {
//    myCollision = new MockCollision;
//    MapGenerator myGen(difficulty);
//    myMap = myGen.getVector();
//}
//
//ServerState::ServerState(Collision* clsnPtr, int difficulty) : myCollision(clsnPtr) {
//    myHost = new MockHost;
//    MapGenerator myGen(difficulty);
//    myMap = myGen.getVector();
//}
//
//ServerState::ServerState(Host* hstPtr, Collision* clsnPtr, int difficulty) : myHost(hstPtr), myCollision(clsnPtr) {
//    MapGenerator myGen(difficulty);
//    myMap = myGen.getVector();
//}

ServerState::~ServerState() {

}

void ServerState::gamePreparation() {
//    myHost->getNames();
//    std::string str;
//    bool flag = true;
//    while (flag) {
//        str = myHost->getName();  //получаем имена присоединяющихся пользователей
//        players.push_back(new MockCar);  //и создаем для каждого Car
//        flag = false;
//    }
//    std::vector<Car*>::iterator it;
//    it = players.begin();
//    while (it != players.end()) {
//        /*раздать машинкам игроков цвета, стартовые позиции и тп*/
//        ++it;
//    }

    bool flag = true;
    while (flag) {  //проходит один раз т.к. пока что только одиночная игра
        players.push_back(Car(0, 0, 0, 0.5 * screenWidth, screenHeight - carHeight));
        flag = false;
    }
    myMap.insert(myMap.begin(), Obstruction(0,0, -roadHeight));  //Road2
    myMap.insert(myMap.begin(), Obstruction(0, 0, 0));  //Road1
    //потом в myMap идут обычные препятствия
}

//void ServerState::serverLoop() {  //добавить обработку времени
//    float delta;  //изменение времени
//    std::vector<Car>::iterator it;
//    while (true) {
//        it = players.begin();
//        while(true/*it != players.end()*/) {
//            input.push_back(myHost->get());  //прием данных о нажатии Event для каждого игрока
//            ++it;
//            break;
//        }
//        //myCollision = new MockCollision(/*&players, &myMap, input, delta*/);
//        myCollision->calculate(/*&players, &myMap, input, delta*/);
//        it = players.begin();
//        while(true/*it != players.end()*/) {
//            myHost->send(/*composeActualElements()*/);
//            ++it;
//            break;
//        }
//        break;
//    }
//}
//
//void ServerState::exit() {
//
//}