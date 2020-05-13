
#ifndef NFS_NEXT_GEN_SERVERSTATE_H
#define NFS_NEXT_GEN_SERVERSTATE_H

//#include "physics/IElements.h"
//#include "network/network.h"
//#include "../../test/Network/networkMock.h"
#include "logic/MapGenerator.h"
#include "physics/physics.h"
//#include "../../test/Physics/physicsMock.h"

#include <vector>
#include <memory>

template<typename T> using sp_t = std::shared_ptr<T>;
template<typename T> using vsp_t = std::vector<sp_t<T>>;

class ServerState {
    int actElTracker = 2;  //т.к. первые два элемента это дорога
public:
    vsp_t<Obstruction> myMap;
//    Host* myHost;
    vsp_t<Car> players;
//    std::vector<Event*> input;
    Collision myCollision;

    //ServerState();
    ServerState(int difficulty = 5);
//    ServerState(Host* hstPtr, int difficulty = 5);
//    ServerState(Collision* clsnPtr, int difficulty = 5);
//    ServerState(Host* hstPtr, Collision* clsnPtr, int difficulty = 5);
    ~ServerState();
    vsp_t<IGameElement> composeActualElements(vsp_t<IGameElement> &actualElements);
    void gamePreparation();
    void serverLoop();
    void exit();
};

#endif //NFS_NEXT_GEN_SERVERSTATE_H
