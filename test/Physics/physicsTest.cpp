#include "gtest/gtest.h"
//#include "graphicsMock.h"
#include "physicsMock.h"
#include <logic/ServerState.h>


TEST(logicBranchTestExample, PhysicsCollisionTest) {
    MockCollision myMockCollision;
    ServerState myServerState(&myMockCollision);
    EXPECT_CALL(myMockCollision, calculate()).Times(testing::AtLeast(1));

    myServerState.serverLoop();
}
