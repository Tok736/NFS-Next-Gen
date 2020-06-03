#include "logic/GameState.h"
#include <ctime>
#include <unistd.h>
#include <chrono>
#include <thread>

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

    std::chrono::time_point<std::chrono::steady_clock> startChrono;
    std::chrono::time_point<std::chrono::steady_clock> checkChrono;

    std::chrono::time_point<std::chrono::steady_clock> startPause = std::chrono::steady_clock::now();
    std::chrono::time_point<std::chrono::steady_clock> endPause = std::chrono::steady_clock::now();

    auto timeInGame = std::chrono::duration_cast<std::chrono::seconds>((checkChrono - startChrono) - (endPause - startPause)).count();


    myWindow->createTextures();

    float freq;
    int time;

    startChrono = std::chrono::steady_clock::now();

    bool isStrike = false;

    while (myWindow->isOpen()) {

        freq = clock.getClockSec();
        time = clock.getClockSec();

        checkChrono = std::chrono::steady_clock::now();

        auto timeInGame = std::chrono::duration_cast<std::chrono::seconds>((checkChrono - startChrono) - (endPause - startPause)).count();


//        std::cout << "freq = " << freq << '\n' << std::endl;
//        std::cout << "chrono = " << timeInGame << '\n' << std::endl;

        myWindow->handleEvents(actions);
        if (!actions.empty() && actions[0] == endOfTheGame)
            return exitGame;

        else if (!actions.empty() && actions[0] == pauseOfTheGame) {
            startPause = std::chrono::steady_clock::now();
            actions.pop_back();

            switch (pauseWindow(myWindow->getRenderWindow(), timeInGame)) {  // тут возвращается: 1 - заново, 2 - главное меню, 3 - продолжить, 0 - полный выход из игры
                case beginGame:
                    countDown(myWindow->getRenderWindow());
                    return beginGame;
                    break;
                case mainMenu:
                    return mainMenu;
                    break;
                case continueGame:
                    break;
                case exitGame:
                    return exitGame;
                    break;
                default:
                    break;

            }
            endPause = std::chrono::steady_clock::now();

        } else {
            if (!actions.empty())
                action = actions[0];
            else
                action = myNoAction;

                myCollision->setTime(timeInGame);

//                myCollision->setAction(myMap, players, actions, isStrike);

                updateAndComposeActualElements(actualElements, actions, isStrike);

//                myCollision->setAction(myMap, players, actions, isStrike, distancePerFrame);


                int ffreq = timeInGame;
                myWindow->render(actualElements, action, ffreq, isStrike);
                myWindow->display();
                isStrike = false;

                //проверка здоровья
                if ((*(actualElements.end() - 1))->getHealthCount() <= 0) {
                    myDB.setUserLocalScore(timeInGame);
                    displayGameOver(myWindow->getRenderWindow(), timeInGame);
                    return 2;
                }

//                if (actualElements.size() == 3 && timeInGame > 10) makeNewMap();

                //добавление босса
                if (actualElements.size() == 3) {
                    myMap.push_back(std::make_shared<Obstruction>(10, 450, 100));
                    bossTracker = myMap.size() - 1;
//                    --actElTracker;
                }

//                usleep(16000); // 50 fps, если считать, что все исполняется в пределах 40 мс

                //для 50 fps:
                distancePerFrame = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - checkChrono).count() * players[0]->getV());
                distanceAtAll += distancePerFrame;
                std::cout << distanceAtAll << " : "<< distancePerFrame << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(20) - std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - checkChrono));
        }


    }

    return 0;
}

void GameState::updateAndComposeActualElements(vsp_t<IGameElement> &actualElements, std::vector<int>& actions, bool& isStrike) {

    //в актуальные попадают элементы с y=[-100; height + 100]
    //первые два эл-та - дорога, потом - препятстивия, в конце - машинка
    actualElements.clear();

    actualElements.push_back(myMap[0]);
    actualElements.push_back(myMap[1]);

    static short bossSpeed = 8;
    static auto prevShot = std::chrono::steady_clock::now();

    int iterator = actElTracker;
    if (actElTracker < bossTracker) {
        while (iterator < myMap.size() && (myMap[iterator]->getY() + distanceAtAll) > -100) {
            if (myMap[iterator]->getY() < (height + 100)) {

                myMap[iterator]->setY(myMap[iterator]->getY() + distancePerFrame);
                actualElements.push_back(myMap[iterator]);
                ++iterator;

            } else {
                ++iterator;
                ++actElTracker;
            }
        }
    } else {

        //движение босса
        if (myMap[bossTracker]->getX()< 450 || myMap[bossTracker]->getX() > width + 378) {
            bossSpeed *= -1;
        }
        myMap[bossTracker]->setX(myMap[bossTracker]->getX() + bossSpeed);
        actualElements.push_back(myMap[bossTracker]);

        //стрельба босса
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - prevShot).count() % 1000 >= rand() % 1000 + 700) {
            prevShot = std::chrono::steady_clock::now();
            myMap.push_back(std::make_shared<Obstruction>(15, myMap[bossTracker]->getX(), myMap[bossTracker]->getY()));
        }
        if (bossTracker < myMap.size() - 1) {
            for (size_t i = bossTracker + 1; i < myMap.size(); ++i) {
                if (myMap[i]->getY() < height + 100) {
                    myMap[i]->setY(myMap[i]->getY() + distancePerFrame);
                    actualElements.push_back(myMap[i]);
                } else {
                    myMap.erase(myMap.begin() + i);
                }
            }
        }

    }

    myCollision->setAction(myMap, players, actions, isStrike, distancePerFrame);

    vsp_t<Car>::const_iterator it;
    it = players.begin();
    while (it != players.end()) {
        actualElements.push_back(*it);
        ++it;
    }

    return;
}


void GameState::gamePreparation() {

    //добавляем машинку игрока в вектор players
    players.push_back(std::make_shared<Car>(2, 0, 0.5 * screenWidth, screenHeight - carHeight));

    //в вектор карты myMap добавляем сменяющие друг друга объекты дороги (занимают первые два элемента в myMap)
    myMap.insert(myMap.begin(), std::make_shared<Obstruction>(0,0, -roadHeight));  //Road2
    myMap.insert(myMap.begin(), std::make_shared<Obstruction>(0, 0, 0));  //Road1
    //потом в myMap идут обычные препятствия

    boss = std::make_shared<Obstruction>(10, rand() % width, 100);
}

void GameState::makeNewMap() {
        sp_t<Obstruction> tempRoad1 = myMap[0];
        sp_t<Obstruction> tempRoad2 = myMap[1];
        myMap.clear();
        MapGenerator myGen;
        myMap = myGen.getVector();
        myMap.insert(myMap.begin(), tempRoad2);  //Road2
        myMap.insert(myMap.begin(), tempRoad1);  //Road1

        actElTracker = 2;

}