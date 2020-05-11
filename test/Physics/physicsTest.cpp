#include "gtest/gtest.h"
//#include "graphicsMock.h"
#include "physicsMock.h"
#include <logic/ServerState.h>
#include <logic/ClientState.h>


TEST(logicBranchTestExample, PhysicsCollisionTest) {
    MockCollision myMockCollision;
    ServerState myServerState(&myMockCollision);
    EXPECT_CALL(myMockCollision, calculate()).Times(testing::AtLeast(1));

    myServerState.serverLoop();
}

class PhysicsDBFixture : public ::testing::Test {
protected:
    MockAbstractDataBase myMockDB;
    ClientState* myClientState;

    virtual void SetUp() {
        myClientState = new ClientState(&myMockDB);
    }

    virtual void TearDown() {
        delete myClientState;
    }
};

TEST_F(PhysicsDBFixture, PhysicsDBTest) {
    EXPECT_CALL(myMockDB, getAutorizeUser(std::string(), std::string())).Times(testing::AtLeast(1));
    EXPECT_CALL(myMockDB, getUserNickname(int())).Times(testing::AtLeast(1));

    myClientState->clientPreparation();
}

TEST_F(PhysicsDBFixture, PhysicsDBExpTest) {
    EXPECT_CALL(myMockDB, getExperience()).Times(testing::AtLeast(1));

    myClientState->exit();
}