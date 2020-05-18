//
// Created by margot on 11.05.2020.
//

#include "graphics/graphic.h"
#include "physics/physics.h"

short int pauseWindow(std::shared_ptr<Window> &window,const int &timeInGame)
{
    Window::createRenderWindow(window, screenWidth, screenHeight, "Pause");
    return isPause(window, timeInGame);
}

short int isPause(std::shared_ptr<Window> &window,const int &timeInGame)
{
    sf::Texture menuBackground;
    menuBackground.loadFromFile("src/textures/bgPause.png");
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
    std::string scoreString("Your score: " + toString(timeInGame) + "!");
    sf::Text continueGame("Continue", font, 60), startAgain("Start again", font, 60), exitFromGame("Exit", font, 60), score(scoreString, font, 70);
//    score.setFillColor(sf::Color(33,255,130));
//    continueGame.setFillColor(sf::Color(255,255,255));
//    startAgain.setFillColor(sf::Color(255,255,255));
//    exitFromGame.setFillColor(sf::Color(255,255,255));
    score.setPosition(screenWidth/4, screenHeight/10);
    continueGame.setPosition(screenWidth/9, screenHeight/3);
    startAgain.setPosition(screenWidth/9, 4*screenHeight/9);
    exitFromGame.setPosition(screenWidth/9, 5*screenHeight/9);
    window->draw(score);
    window->draw(continueGame);
    window->draw(startAgain);
    window->draw(exitFromGame);

    sf::Event event;
    while (!start)
    {
//        score.setFillColor(sf::Color(33,255,130));
//        continueGame.setFillColor(sf::Color(255,255,255));
//        startAgain.setFillColor(sf::Color(255,255,255));
//        exitFromGame.setFillColor(sf::Color(255,255,255));
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
            //continue Game
            if (sf::IntRect((float)window->getWidth()/ 9 - xProcentUpdate, (float)window->getHeight()/3 + 30*yProcentUpdate, 400*xProcentUpdate, 90*yProcentUpdate).contains(
                    sf::Mouse::getPosition(*window->getWindow()))) {
//                continueGame.setFillColor(sf::Color(1,255,244));
                menuNum = 2;
            }
            //restart Game
            if (sf::IntRect((float)window->getWidth()/ 9 - xProcentUpdate, (float)4*window->getHeight()/9 + 30*yProcentUpdate, 400*xProcentUpdate, 90*yProcentUpdate).contains(
                    sf::Mouse::getPosition(*window->getWindow()))) {
//                startAgain.setFillColor(sf::Color(235, 230, 9));
                menuNum = 3;
            }
            //Exit
            if (sf::IntRect((float)window->getWidth()/ 9 - xProcentUpdate, (float)5*window->getHeight()/9 + 30*yProcentUpdate, 200*xProcentUpdate, 90*yProcentUpdate).contains(
                    sf::Mouse::getPosition(*window->getWindow()))) {
//                exitFromGame.setFillColor(sf::Color(82,43,255));
                menuNum = 4;
            }
            //handle Pressed Button
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                //pressed Single Game
                if (menuNum == 2) {
                    continueGame.setCharacterSize(50);
                    window->draw(menuBg);
                    window->draw(score);
                    window->draw(continueGame);
                    window->draw(startAgain);
                    window->draw(exitFromGame);
                    window->display();
                    window->clear();
                    usleep(200000);
                    continueGame.setCharacterSize(60);
                    window->draw(menuBg);
                    window->draw(score);
                    window->draw(continueGame);
                    window->draw(startAgain);
                    window->draw(exitFromGame);
                    window->display();
                    usleep(100000);
                    window->clear();
                    return 1; //single
                }
                if (menuNum == 3)
                {

                    return 2;
                }
                //pressed Exit
                if (menuNum == 4)
                {
                    exitFromGame.setCharacterSize(50);
                    window->draw(menuBg);
                    window->draw(score);
                    window->draw(continueGame);
                    window->draw(startAgain);
                    window->draw(exitFromGame);
                    window->display();
                    window->clear();
                    usleep(200000);
                    exitFromGame.setCharacterSize(60);
                    window->draw(menuBg);
                    window->draw(score);
                    window->draw(continueGame);
                    window->draw(startAgain);
                    window->draw(exitFromGame);
                    window->display();
                    window->close();
                    return 0;
                }
            }
        }
        window->draw(menuBg);
        window->draw(score);
        window->draw(continueGame);
        window->draw(startAgain);
        window->draw(exitFromGame);
        window->display();
    }
    return 0;
}