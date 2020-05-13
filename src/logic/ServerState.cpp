#include "logic/ServerState.h"

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

void ServerState::composeActualElements(vsp_t<IGameElement> &actualElements) {

    //в актуальные попадают элементы с y=[-100; height + 100]

    actualElements.clear();

    actualElements.push_back(myMap[0]);
    actualElements.push_back(myMap[1]);

    int iterator = actElTracker;
    while (iterator < myMap.size() && myMap[iterator]->getY() >= -100) {
        if (myMap[iterator]->getY() <= (height + 100)) {
                actualElements.push_back(myMap[iterator]);
                ++iterator;
        } else {
            ++iterator;
            ++actElTracker;
        }
    }

    vsp_t<Car>::const_iterator it;
    it = players.begin();
    while (it != players.end()) {
        actualElements.push_back(*it);
        ++it;
    }

    return;
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
        players.push_back(std::make_shared<Car>(1, 0, 0, 0.5 * screenWidth, screenHeight - carHeight));
        flag = false;
    }
    myMap.insert(myMap.begin(), std::make_shared<Obstruction>(0,0, -roadHeight));  //Road2
    myMap.insert(myMap.begin(), std::make_shared<Obstruction>(0, 0, 0));  //Road1
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