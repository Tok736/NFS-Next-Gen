#ifndef NFS_NEXT_GEN_CLIENTSTATE_H
#define NFS_NEXT_GEN_CLIENTSTATE_H

//#include "physics/IElements.h"
//#include "GameData.h"
//#include "Client.h"
#include "graphics/graphic.h"
//#include "../../test/Graphics/graphicsMock.h"
//#include "network/network.h"
//#include "../../test/Network/networkMock.h"
#include "physics/physics.h"
//#include "../../test/Physics/physicsMock.h"
#include "logic/ServerState.h"

//#include "IDataBase.h"

#include <vector>
#include <memory>

template<typename T> using sp_t = std::shared_ptr<T>;
template<typename T> using vsp_t = std::vector<sp_t<T>>;


class ClientState {
public:
    vsp_t<IGameElement> actualElements;
//    GameData data;
    sp_t<ServerState> myServerState;  //пока нет сети, пусть серверная часть будет внутри клиентской
    sp_t<Window> myWindow;
//    Event* myEvent;
//    AbstractDataBase* myDB;
//    Client* myClient;

    ClientState();
    ClientState(sp_t<Window> wndPtr, sp_t<ServerState>);
//    ClientState(sp_t<Window> wndPtr);
//    ClientState(Event* evntPtr);
//    ClientState(Client* clntPtr);
//    ClientState(AbstractDataBase* dbPtr);
//    ClientState(sp_t<Window> wndPtr, Event* evntPtr, Client* clntPtr, AbstractDataBase* dbPtr);
    ~ClientState();
//    ClientState(char* hostIp, char* playerName);
//    void clientPreparation();
    void clientLoop();
//    void exit();
};

#endif //NFS_NEXT_GEN_CLIENTSTATE_H
