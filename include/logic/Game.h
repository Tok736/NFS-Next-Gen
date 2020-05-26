#ifndef NFS_NEXT_GEN_GAME_H
#define NFS_NEXT_GEN_GAME_H

#include "logic/GameState.h"

//#include "physics/IElements.h"
//#include "GameData.h"
//#include "Client.h"
#include "graphics/graphic.h"
//#include "../../test/Graphics/graphicsMock.h"
//#include "network/network.h"
//#include "../../test/Network/networkMock.h"
#include "physics/physics.h"
//#include "../../test/Physics/physicsMock.h"

//#include "IDataBase.h"

#include <vector>
#include <memory>

template<typename T> using sp_t = std::shared_ptr<T>;
template<typename T> using vsp_t = std::vector<sp_t<T>>;


class Game {
    sp_t<GameState> myGameState;

//    void exitGame();
public:
    Game();
    ~Game();
    size_t loginMenu(sp_t<Window>, SQLiteDataBase&);  //тут логин/регистрация
    void play();
};

#endif //NFS_NEXT_GEN_GAME_H
