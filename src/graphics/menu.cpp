//
// Created by margot on 02.05.2020.
//

#include "graphics/graphic.h"
#include "phisics/physics.h"

bool displayMenu(std::shared_ptr<Window> &window)
{
    Window::createRenderWindow(window, screenWidth, screenHeight, "Menu");
    return isMenu(window);
}

bool isMenu(std::shared_ptr<Window> &window)
{
    sf::Texture buttonStart, buttonStartPress, nameOfGame, menuBackground;
    buttonStart.loadFromFile("src/textures/buttonStart.png");
    buttonStartPress.loadFromFile("src/textures/buttonStartPress.png");
    menuBackground.loadFromFile("src/textures/menu.png");
    nameOfGame.loadFromFile("src/textures/nameOfGame.png");
    sf::Sprite menu1(buttonStart), menuBg(menuBackground), gameName(nameOfGame);
    int menuNum = 0;
    int start = 0;
    menu1.setPosition(screenWidth/2-90, screenHeight/2-50);
    menuBg.setPosition(0,0);
    gameName.setPosition(1*screenWidth/4, screenHeight/8);

    float xProcentUpdate = 1;
    float yProcentUpdate = 1;
    window->setWidth(screenWidth);
    window->setHeight(screenHeight);


    sf::Event event;
    while (!start)
    {
        menu1.setTexture(buttonStart);
        menuNum = 0;
        window->clear();
        if (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            {
                window->close();
                return false;
            }
            if (event.type == sf::Event::Resized)
            {
                window->setHeight(static_cast<unsigned int>(event.size.height));
                window->setWidth(static_cast<unsigned int>(event.size.width));
                xProcentUpdate = window->getWidth()/screenWidth;
                yProcentUpdate = window->getHeight()/screenHeight;
                if (yProcentUpdate == 0)
                    yProcentUpdate = 1;
                if (xProcentUpdate == 0)
                    xProcentUpdate = 1;
            }
            if (sf::IntRect(window->getWidth()/ 2 - 90*xProcentUpdate, window->getHeight()/ 2 - 50*yProcentUpdate, 200*xProcentUpdate, 90*yProcentUpdate).contains(
                    sf::Mouse::getPosition(*window->getWindow()))) {
                menu1.setTexture(buttonStartPress);
                menuNum = 1;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (menuNum == 1) {
                    window->clear();
                    start = 1;
                }
            }
        }
        window->draw(menuBg);
        window->draw(menu1);
        window->draw(gameName);

        window->display();
    }
    return true;
};

