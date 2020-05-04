#include "gtest/gtest.h"
#include "networkMock.h"
#include "logic/ClientState.h"
#include "logic/ServerState.h"

class NetworkClientFixture : public ::testing::Test {
protected:
    MockClient myMockClient;
    ClientState* myClientState;

    virtual void SetUp() {
        myClientState = new ClientState(&myMockClient);
    }

    virtual void TearDown() {
        delete myClientState;
    }
};

TEST_F(NetworkClientFixture, NetworkClientSendGetTest) {
    EXPECT_CALL(myMockClient, send()).Times(testing::AtLeast(1));
    EXPECT_CALL(myMockClient, get()).Times(testing::AtLeast(1));

    myClientState->clientLoop();
}

TEST_F(NetworkClientFixture, NetworkClientSendNameTest) {
    EXPECT_CALL(myMockClient, sendName(std::string())).Times(testing::AtLeast(1));

    myClientState->clientPreparation();
}

class NetworkHostFixture : public ::testing::Test {
protected:
    MockHost myMockHost;
    ServerState* myServerState;

    virtual void SetUp() {
        myServerState = new ServerState(&myMockHost);
    }

    virtual void TearDown() {
        delete myServerState;
    }
};

TEST_F(NetworkHostFixture, NetworkHostGetSendTest) {
    EXPECT_CALL(myMockHost, get()).Times(testing::AtLeast(1));
    EXPECT_CALL(myMockHost, send()).Times(testing::AtLeast(1));

    myServerState->serverLoop();
}

TEST_F(NetworkHostFixture, NetworkHostGetNameTest) {
    EXPECT_CALL(myMockHost, getName()).Times(testing::AtLeast(1));

    myServerState->gamePreparation();
}
