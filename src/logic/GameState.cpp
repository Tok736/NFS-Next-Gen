#include "logic/GameState.h"
#include <ctime>
#include <unistd.h>

const float timeForFrame = 0.033;  //for 30 fps

GameState::GameState() {
    myWindow = std::make_shared<Window>();
    myCollision = std::make_shared<Collision>();
    MapGenerator myGen;
    myMap = myGen.getVector();
//    SQLiteDataBase myDB;
}

GameState::GameState(sp_t<Window> wndPtr) : myWindow(wndPtr) {
    myCollision = std::make_shared<Collision>();
    MapGenerator myGen;
    myMap = myGen.getVector();
//    SQLiteDataBase myDB;
}


GameState::~GameState() {}

size_t GameState::gameLoop(SQLiteDataBase &myDB) {

    Clock clock;
    vector<int> actions;
    int action;
    gamePreparation();


    myWindow->createTextures();

    float freq;
    int time;

//    int timeBefore;
//    int timeAfter;
    bool isStrike = false;

    while (myWindow->isOpen()) {

//        timeBefore = std::clock();

        freq = clock.getClockSec();
        time = clock.getClockSec();
        myWindow->handleEvents(actions);
        if (!actions.empty() && actions[0] == endOfTheGame)
//            myWindow->close();
            return 0;
        else if (!actions.empty() && actions[0] == pauseOfTheGame) {
            actions.pop_back();
            switch (pauseWindow(myWindow->getRenderWindow(), freq)) {  // тут возвращается: 1 - продолжить, 2 - заново, 0 - выход в меню (надо переделать цифры для красоты)
                case 1:
                    countDown(myWindow->getRenderWindow());
                    return 1;
                    break;
                case 2:
                    return 2;
                    break;
                case 3:
                    break;
                case 0:
                    return 0;
                    break;
                default:
                    break;
            }
        } else {
            if (!actions.empty())
                action = actions[0];
            else
                action = myNoAction;

            myCollision->setTime(time);
            myCollision->setAction(myMap, players, actions, isStrike);
        }

        //Проверка здоровья:
//        vsp_t<Car>::const_iterator it;
//        it = players.begin();
//        while (it != players.end()) {
//            if ((*it)->getHealthCount() <= 0) return;
//            ++it;
//        }

        composeActualElements(actualElements);




        int ffreq = (int) freq;
        myWindow->render(actualElements, action, ffreq, isStrike);
        myWindow->display();
        isStrike = false;

        if ((*(actualElements.end() - 1))->getHealthCount() <= 0) {
            myDB.setUserLocalScore(freq);
            displayGameOver(myWindow->getRenderWindow(), freq);
            return 2;
        }


//        timeAfter = std::clock();
        usleep(16000); // 50 fps, если считать, что все исполняется в пределах 40 мс
//        sleep(timeForFrame - ((float)(timeAfter - timeBefore) / CLOCKS_PER_SEC));  //for 30fps
//        std::cout << "time for frame: " << timeForFrame- ((float)(timeAfter - timeBefore) / CLOCKS_PER_SEC) << std::endl;
//        std::cout << "before: " << timeBefore << std::endl;
//        std::cout << "after: " << timeAfter << std::endl;

    }
    return 0;
}

void GameState::composeActualElements(vsp_t<IGameElement> &actualElements) {

    //в актуальные попадают элементы с y=[-100; height + 100]
    //первые два эл-та - дорога, потом - препятстивия, в конце - машинка
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


void GameState::gamePreparation() {
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
        players.push_back(std::make_shared<Car>(2, 0, 0.5 * screenWidth, screenHeight - carHeight));
        flag = false;
    }
    myMap.insert(myMap.begin(), std::make_shared<Obstruction>(0,0, -roadHeight));  //Road2
    myMap.insert(myMap.begin(), std::make_shared<Obstruction>(0, 0, 0));  //Road1
    //потом в myMap идут обычные препятствия
}

//void ClientState::exit() {
//    myDB->getExperience();
//    myWindow->close();
//}
