
#ifndef NFS_NEXT_GEN_SERVERSTATE_H
#define NFS_NEXT_GEN_SERVERSTATE_H

#include "IElement.h"
#include "Car.h"
#include "Collision.h"
#include "Host.h"
#include "graphic.h"

#include <vector>
#include <memory>

class ClientState {
public:
    std::vector<std::shared_ptr<IGameElement>> myMap;
    Host myHost;
    std::vector<Car> players;
    std::vector<Event> input;
    Collision myCollision;

    ServerState();
    std::vector<std::shared_ptr<IGameElement>> composeActualElements;
    void gamePreparation;
    void serverLoop();
    void exit();
};

#endif //NFS_NEXT_GEN_SERVERSTATE_H
