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


class GameState {
    int actElTracker = 2;  //для composeActualElements (2 т.к. первые два элемента это дорога)
public:
    vsp_t<IGameElement> actualElements;
    sp_t<Window> myWindow;
    vsp_t<Obstruction> myMap;
    vsp_t<Car> players;
//    std::vector<Event*> input;
    sp_t<Collision> myCollision;
//    SQLiteDataBase myDB;

//    Event* myEvent;
//    Client* myClient;

    GameState();
    GameState(sp_t<Window> wndPtr);
    ~GameState();
    size_t gameLoop(SQLiteDataBase &myDB);  //0 - выход в главное меню, 2 - играть заново
    void composeActualElements(vsp_t<IGameElement> &actualElements);
    void gamePreparation();
    void serverLoop();
    void exit();
};


#endif //NFS_NEXT_GEN_GAMESTATE_H
