#ifndef NFS_NEXT_GEN_GAME_H
#define NFS_NEXT_GEN_GAME_H

#include "logic/ClientState.h"
#include "logic/ServerState.h"

#include "graphics/graphic.h"
#include "physics/physics.h"

#include <vector>
#include <memory>

template<typename T> using sp_t = std::shared_ptr<T>;
template<typename T> using vsp_t = std::vector<sp_t<T>>;


class Game {
    sp_t<ClientState> myClientState;
    sp_t <ServerState> myServerState;
public:
    Game();
    ~Game();
    void playGame();
};

#endif //NFS_NEXT_GEN_GAME_H
