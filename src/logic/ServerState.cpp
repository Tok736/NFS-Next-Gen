#include "logic/ServerState.h"

ServerState::ServerState(int difficulty) {
//    myHost = new MockHost;
    myCollision = Collision();
    MapGenerator myGen(difficulty);
    myMap = myGen.getVector();
}

ServerState::~ServerState() {

}

void ServerState::composeActualElements(vsp_t<IGameElement> &actualElements) {

    //в актуальные попадают элементы с y=[-100; height + 100]

    actualElements.clear();

    actualElements.push_back(myMap[0]);
    actualElements.push_back(myMap[1]);

    int iterator = actElTracker;
    while (iterator < myMap.size() && myMap[iterator]->getY() > -100) {
        if (myMap[iterator]->getY() < (height + 100)) {
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

    bool flag = true;
    while (flag) {  //проходит один раз т.к. пока что только одиночная игра
        players.push_back(std::make_shared<Car>(1, 0, 0, 0.5 * screenWidth, screenHeight - carHeight));
        flag = false;
    }
    myMap.insert(myMap.begin(), std::make_shared<Obstruction>(0,0, -roadHeight));  //Road2
    myMap.insert(myMap.begin(), std::make_shared<Obstruction>(0, 0, 0));  //Road1
    //потом в myMap идут обычные препятствия
}
