#ifndef NFS_NEXT_GEN_CLIENTSTATE_H
#define NFS_NEXT_GEN_CLIENTSTATE_H

#include "IElement.h"
#include "GameData.h"
#include "Client.h"
#include "graphic.h"
#include "IDataBase.h"

#include <vector>
#include <memory>

class ClientState {
public:
    std::vector<std::shared_ptr<IGameElement>> actualElements;
    GameData data;
    Window myWindow;
    Event myEvent;
    AbstractDataBase myDB;
    Client myClient;

    ClientState();
    void clientLoop();
    void exit();
};

#endif //NFS_NEXT_GEN_CLIENTSTATE_H
