
#ifndef NFS_NEXT_GEN_SERVERSTATE_H
#define NFS_NEXT_GEN_SERVERSTATE_H

#include "physics/IElements.h"
#include "network/network.h"
#include "../../test/Network/networkMock.h"
#include "logic/MapGenerator.h"
#include "physics/physics.h"
#include "../../test/Physics/physicsMock.h"

#include <vector>
#include <memory>

class ServerState {
public:
    std::vector<std::shared_ptr<IGameElement>> myMap;
    Host* myHost;
    std::vector<Car*> players;
    std::vector<Event*> input;
    Collision* myCollision;

    //ServerState();
    ServerState(int difficulty = 5);
    ServerState(Host* hstPtr, int difficulty = 5);
    ServerState(Collision* clsnPtr, int difficulty = 5);
    ServerState(Host* hstPtr, Collision* clsnPtr, int difficulty = 5);
    ~ServerState();
    std::vector<std::shared_ptr<IGameElement>> composeActualElements;
    void gamePreparation();
    void serverLoop();
    void exit();
};

#endif //NFS_NEXT_GEN_SERVERSTATE_H
