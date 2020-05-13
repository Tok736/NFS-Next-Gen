#ifndef NFS_NEXT_GEN_CLIENTSTATE_H
#define NFS_NEXT_GEN_CLIENTSTATE_H
#include "graphics/graphic.h"
#include "physics/physics.h"
#include "logic/ServerState.h"


#include <vector>
#include <memory>

template<typename T> using sp_t = std::shared_ptr<T>;
template<typename T> using vsp_t = std::vector<sp_t<T>>;


class ClientState {
public:
    vsp_t<IGameElement> actualElements;
    sp_t<ServerState> myServerState;  //пока нет сети, пусть серверная часть будет внутри клиентской
    sp_t<Window> myWindow;

    ClientState();
    ClientState(sp_t<Window> wndPtr, sp_t<ServerState>);
    ~ClientState();
    void clientLoop();
};

#endif //NFS_NEXT_GEN_CLIENTSTATE_H
