//
// Created by margot on 02.05.2020.
//

#include "gtest/gtest.h"
#include "physicsMock.h"
#include "graphics/graphic.h"


TEST(graphicBranchTestExample, physicsCarTest) {
    MockCar myMockCar;
    MockObstruction myObstructions;

    auto *window = new Window;
    Window::createRenderWindow(window, screenLength, screenWidth, "Game");

    vector<MockObstruction> elements;
    vector<MockCar> cars;

    window->render(cars, elements);
    EXPECT_CALL(myMockCar,getX()).Times(testing::AtLeast(1));
}