#include "gtest/gtest.h"
#include "graphicsMock.h"
#include "logic/ClientState.h"

TEST(logicBranchTestExample, GraphicsWindowTest) {
    MockWindow myMockWindow;
    ClientState myClientState(&myMockWindow);
    EXPECT_CALL(myMockWindow, createRenderWindow()).Times(testing::AtLeast(1));
    EXPECT_CALL(myMockWindow, render()).Times(testing::AtLeast(1));
    EXPECT_CALL(myMockWindow, close()).Times(testing::AtLeast(1));

    myClientState.clientLoop();
}

TEST(logicBranchTestExample, GraphicsEventTest) {
    MockEvent myMockEvent;
    ClientState myClientState(&myMockEvent);
    EXPECT_CALL(myMockEvent, getEvent()).Times(testing::AtLeast(1));

    myClientState.clientLoop();
}