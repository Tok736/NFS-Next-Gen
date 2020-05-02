//
// Created by margot on 30.04.2020.
//


#include "gtest/gtest.h"
#include "../include/graphics/graphic.h"


void Window::render(std::vector<Car> cars, std::vector<Obstruction> roadElements) {
    renderWindow_->clear();
    sf::Texture roadTexture1, roadTexture2;
    roadTexture1.loadFromFile("/home/margot/testGame/testAll/textures/littleRoad.png");
    roadTexture2.loadFromFile("/home/margot/testGame/testAll/textures/littleRoad.png");
    sf::Sprite roadSprite1(roadTexture1);
    sf::Sprite roadSprite2(roadTexture2);
    roadSprite1.setPosition((float) roadElements[0].getX(), (float) roadElements[0].getY());
    roadSprite2.setPosition((float) roadElements[1].getX(), (float) roadElements[1].getY());
    renderWindow_->draw(roadSprite1);
    renderWindow_->draw(roadSprite2);

    for (auto &car : cars) {
        sf::Texture carTexture;
        carTexture.loadFromFile("/home/margot/testGame/testAll/textures/Car_0.png");
        sf::Sprite carSprite(carTexture);
        carSprite.setPosition((float) car.getX(), (float) car.getY());
        renderWindow_->draw(carSprite);
    }
}


TEST(googleTestExample, graphicTest) {
    std::cout << "Graphic test\n";
}