#include "gtest/gtest.h"
#include "networkMock.h"
#include "logic/ClientState.h"
#include "logic/ServerState.h"

TEST(logicBranchTestExample, NetworkClientTest) {
    MockClient myMockClient;
    ClientState myClientState(&myMockClient);
    EXPECT_CALL(myMockClient, sendName()).Times(testing::AtLeast(1));
    EXPECT_CALL(myMockClient, send()).Times(testing::AtLeast(1));
    EXPECT_CALL(myMockClient, get()).Times(testing::AtLeast(1));

    myClientState.clientLoop();
}

TEST(logicBranchTestExample, NetworkHostGetSendTest) {
    MockHost myMockHost;
    ServerState myServerState(&myMockHost);
    EXPECT_CALL(myMockHost, get()).Times(testing::AtLeast(1));
    EXPECT_CALL(myMockHost, send()).Times(testing::AtLeast(1));

    myServerState.serverLoop();
}

TEST(logicBranchTestExample, NetworkHostGetNameTest) {
    MockHost myMockHost;
    ServerState myServerState(&myMockHost);
    EXPECT_CALL(myMockHost, getName()).Times(testing::AtLeast(1));

    myServerState.gamePreparation();
}
