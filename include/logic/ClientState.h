#ifndef NFS_NEXT_GEN_CLIENTSTATE_H
#define NFS_NEXT_GEN_CLIENTSTATE_H

#include "physics/IElements.h"
//#include "GameData.h"
//#include "Client.h"
#include "graphics/graphic.h"
#include "../../test/Graphics/graphicsMock.h"
#include "network/network.h"
#include "../../test/Network/networkMock.h"
#include "physics/physics.h"
#include "../../test/Physics/physicsMock.h"

//#include "IDataBase.h"

#include <vector>
#include <memory>

class ClientState {
public:
    std::vector<std::shared_ptr<IGameElement>> actualElements;
//    GameData data;
    Window* myWindow;
    Event* myEvent;
    AbstractDataBase* myDB;
    Client* myClient;

    ClientState();
    ClientState(Window* wndPtr);
    ClientState(Event* evntPtr);
    ClientState(Client* clntPtr);
    ClientState(AbstractDataBase* dbPtr);
    ClientState(Window* wndPtr, Event* evntPtr, Client* clntPtr, AbstractDataBase* dbPtr);
    ~ClientState();
//    ClientState(char* hostIp, char* playerName);
    void clientPreparation();
    void clientLoop();
    void exit();
};

#endif //NFS_NEXT_GEN_CLIENTSTATE_H
