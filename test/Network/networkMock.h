#ifndef NFS_NEXT_GEN_NETWORKMOCK_H
#define NFS_NEXT_GEN_NETWORKMOCK_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "network/network.h"
#include "physics/IElements.h"
#include "graphics/graphic.h"

#include <vector>
#include <memory>

class MockClient : public Client {
public:
    MOCK_METHOD0(send, void());
    MOCK_METHOD0(sendName, void());
    MOCK_METHOD0(get, std::vector<std::shared_ptr<IGameElement>>());
};

class MockHost : public Host {
public:
    MOCK_METHOD0(send, void());
    MOCK_METHOD0(get, Event*());
    MOCK_METHOD0(getName, std::string());
};

#endif //NFS_NEXT_GEN_NETWORKMOCK_H
