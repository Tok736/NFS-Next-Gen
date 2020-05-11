//
// Created by margot on 02.05.2020.
//

#include "graphics/graphic.h"
#include "phisics/physics.h"

short int displayMenu(std::shared_ptr<Window> &window)
{
    Window::createRenderWindow(window, screenWidth, screenHeight, "Menu");
    return isMenu(window);
}

short int isMenu(std::shared_ptr<Window> &window)
{
    sf::Texture menuBackground;
    menuBackground.loadFromFile("src/textures/bg.png");
    sf::Sprite menuBg(menuBackground);
    int menuNum = 0;
    int start = 0;
    menuBg.setPosition(0,0);

    float xProcentUpdate = 1;
    float yProcentUpdate = 1;
    window->setWidth(screenWidth);
    window->setHeight(screenHeight);

    sf::Font font;
    font.loadFromFile("src/fonts/fontForScore.ttf");
    sf::Text singleGame("Single game", font, 60), coopGame("Online game", font, 60), exitFromGame("Exit", font, 60);
    singleGame.setFillColor(sf::Color(255,255,255));
    coopGame.setFillColor(sf::Color(255,255,255));
    exitFromGame.setFillColor(sf::Color(255,255,255));
    singleGame.setPosition(screenWidth/9, screenHeight/3);
    coopGame.setPosition(screenWidth/9, 4*screenHeight/9);
    exitFromGame.setPosition(screenWidth/9, 5*screenHeight/9);
    window->draw(singleGame);
    window->draw(coopGame);
    window->draw(exitFromGame);

    sf::Event event;
    while (!start)
    {
        singleGame.setFillColor(sf::Color(255,255,255));
        coopGame.setFillColor(sf::Color(255,255,255));
        exitFromGame.setFillColor(sf::Color(255,255,255));
        menuNum = 0;
        window->clear();
        if (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
                return 0;
            }
            if (event.type == sf::Event::Resized)
            {
                window->setHeight(static_cast<unsigned int>(event.size.height));
                window->setWidth(static_cast<unsigned int>(event.size.width));
                xProcentUpdate = (float)window->getWidth()/screenWidth;
                yProcentUpdate = (float)window->getHeight()/screenHeight;
                if (yProcentUpdate == 0)
                    yProcentUpdate = 1;
                if (xProcentUpdate == 0)
                    xProcentUpdate = 1;
            }
            //Single Game
            if (sf::IntRect((float)window->getWidth()/ 9 - xProcentUpdate, (float)window->getHeight()/3 + 30*yProcentUpdate, 400*xProcentUpdate, 90*yProcentUpdate).contains(
                    sf::Mouse::getPosition(*window->getWindow()))) {
                singleGame.setFillColor(sf::Color(83,15,173));
                menuNum = 2;
            }
            //Coop Game
            if (sf::IntRect((float)window->getWidth()/ 9 - xProcentUpdate, (float)4*window->getHeight()/9 + 30*yProcentUpdate, 400*xProcentUpdate, 90*yProcentUpdate).contains(
                    sf::Mouse::getPosition(*window->getWindow()))) {
                coopGame.setFillColor(sf::Color(255,0,173));
                menuNum = 3;
            }
            //Exit
            if (sf::IntRect((float)window->getWidth()/ 9 - xProcentUpdate, (float)5*window->getHeight()/9 + 30*yProcentUpdate, 200*xProcentUpdate, 90*yProcentUpdate).contains(
                    sf::Mouse::getPosition(*window->getWindow()))) {
                exitFromGame.setFillColor(sf::Color(240,73,60));
                menuNum = 4;
            }
            //handle Pressed Button
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                //pressed Single Game
                if (menuNum == 2) {
                    singleGame.setCharacterSize(40);
                    window->draw(menuBg);
                    window->draw(singleGame);
                    window->draw(coopGame);
                    window->draw(exitFromGame);
                    window->display();
                    window->clear();
                    return 1; //single
                }
                if (menuNum == 3)
                {
                    //coop
                    return 2;
                }
                //pressed Exit
                if (menuNum == 4)
                {
                    exitFromGame.setCharacterSize(40);
                    window->draw(menuBg);
                    window->draw(singleGame);
                    window->draw(coopGame);
                    window->draw(exitFromGame);
                    window->display();
                    window->close();
                    return 0;
                }
            }
        }
        window->draw(menuBg);
        window->draw(singleGame);
        window->draw(coopGame);
        window->draw(exitFromGame);
        window->display();
    }
    return 0;
};

