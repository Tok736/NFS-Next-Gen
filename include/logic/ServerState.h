#ifndef NFS_NEXT_GEN_SERVERSTATE_H
#define NFS_NEXT_GEN_SERVERSTATE_H

#include "logic/MapGenerator.h"
#include "physics/physics.h"

#include <vector>
#include <memory>

template<typename T> using sp_t = std::shared_ptr<T>;
template<typename T> using vsp_t = std::vector<sp_t<T>>;

class ServerState {
    int actElTracker = 2;  //т.к. первые два элемента это дорога
public:
    vsp_t<Obstruction> myMap;
    vsp_t<Car> players;
    Collision myCollision;

    ServerState(int difficulty = 5);
    ~ServerState();
    void composeActualElements(vsp_t<IGameElement> &actualElements);
    void gamePreparation();
    void serverLoop();
    void exit();
};

#endif //NFS_NEXT_GEN_SERVERSTATE_H
