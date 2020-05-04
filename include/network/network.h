#ifndef NFS_NEXT_GEN_NETWORK_H
#define NFS_NEXT_GEN_NETWORK_H

#include "physics/IElements.h"
#include "graphics/graphic.h"

#include <vector>
#include <memory>

class Client {
public:
    virtual void send() = 0;
    virtual void sendName() = 0;
    virtual std::vector<std::shared_ptr<IGameElement>> get() = 0;
};

class Host {
public:
    virtual void send() = 0;
    virtual Event* get() = 0;
    virtual std::string getName() = 0;
};

#endif //NFS_NEXT_GEN_NETWORK_H
