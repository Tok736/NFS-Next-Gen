#include "gtest/gtest.h"
#include "graphicsMock.h"
#include "logic/ClientState.h"


class GraphicsWindowFixture : public ::testing::Test {
protected:
    MockWindow myMockWindow;
    ClientState* myClientState;

    virtual void SetUp() {
        myClientState = new ClientState(&myMockWindow);
    }

    virtual void TearDown() {
        delete myClientState;
    }
};

TEST_F(GraphicsWindowFixture, GraphicsWindowCreateRenderTest) {
    EXPECT_CALL(myMockWindow, createRenderWindow()).Times(testing::AtLeast(1));

    myClientState->clientPreparation();
}

TEST_F(GraphicsWindowFixture, GraphicsWindowRenderTest) {
    EXPECT_CALL(myMockWindow, render()).Times(testing::AtLeast(1));

    myClientState->clientLoop();
}

TEST_F(GraphicsWindowFixture, GraphicsCloseTest) {
    EXPECT_CALL(myMockWindow, close()).Times(testing::AtLeast(1));

    myClientState->exit();
}

TEST(logicBranchTestExample, GraphicsEventTest) {
    MockEvent myMockEvent;
    ClientState myClientState(&myMockEvent);
    EXPECT_CALL(myMockEvent, getEvent()).Times(testing::AtLeast(1));

    myClientState.clientLoop();
}