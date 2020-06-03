#ifndef NFS_NEXT_GEN_GAMESTATE_H
#define NFS_NEXT_GEN_GAMESTATE_H


//#include "physics/IElements.h"
//#include "GameData.h"
//#include "Client.h"
#include "graphics/graphic.h"
//#include "../../test/Graphics/graphicsMock.h"
//#include "network/network.h"
//#include "../../test/Network/networkMock.h"
#include "physics/physics.h"
//#include "../../test/Physics/physicsMock.h"
#include "logic/MapGenerator.h"
#include <physics/SQLite.h>

//#include "IDataBase.h"

#include <vector>
#include <memory>

template<typename T> using sp_t = std::shared_ptr<T>;
template<typename T> using vsp_t = std::vector<sp_t<T>>;

enum scenes {
    beginGame = 1,
    mainMenu = 2,
    continueGame = 3,
    exitGame = 0,
};

class GameState {
    int actElTracker = 2;  //для composeActualElements (2 т.к. первые два элемента это дорога)
    int bossTracker = INT32_MAX;  //начало объектов босса (сам босс и снаряды)
    unsigned int distanceAtAll = 0;  //пройденный путь всего
    unsigned int distancePerFrame = 0;  //пройденный путь за кадр

public:
    vsp_t<IGameElement> actualElements;
    sp_t<Window> myWindow;
    vsp_t<Obstruction> myMap;
    vsp_t<Car> players;
    sp_t<Collision> myCollision;
    sp_t<Obstruction> boss;


    GameState();
    GameState(sp_t<Window> wndPtr);
    ~GameState();
    size_t gameLoop(SQLiteDataBase &myDB);  //0 - выход в главное меню, 2 - играть заново
    void updateAndComposeActualElements(vsp_t<IGameElement>& actualElements, std::vector<int>& actions, bool& isStrike);
    void gamePreparation();
    void makeNewMap();
    void serverLoop();
    void exit();
};


#endif //NFS_NEXT_GEN_GAMESTATE_H
