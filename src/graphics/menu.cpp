//
// Created by margot on 02.05.2020.
//

#include "graphics/graphic.h"
#include "physics/physics.h"

short int displayMenu(std::shared_ptr<Window> &window,const string &name)
{
    Window::createRenderWindow(window, screenWidth, screenHeight, "Menu");
    return isMenu(window, name);
}

short int isMenu(std::shared_ptr<Window> &window,const string& name)
{
    sf::SoundBuffer buffer;
    buffer.loadFromFile("src/sounds/button.ogg");
    sf::Sound sound;
    sound.setBuffer(buffer);

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

    sf::Text playerName("Hello, " + name+"!", font, 65), singleGame("Single game", font, 60), coopGame("Online game", font, 60), exitFromGame("Exit", font, 60);
    playerName.setFillColor(sf::Color::Black);
    singleGame.setFillColor(sf::Color(255,255,255));
    coopGame.setFillColor(sf::Color(255,255,255));
    exitFromGame.setFillColor(sf::Color(255,255,255));
    singleGame.setPosition(screenWidth/9, screenHeight/3);
    coopGame.setPosition(screenWidth/9, 4*screenHeight/9);
    playerName.setPosition(screenWidth/2, screenHeight/2);
    exitFromGame.setPosition(screenWidth/9, 5*screenHeight/9);
    window->draw(playerName);
    window->draw(singleGame);
    window->draw(coopGame);
    window->draw(exitFromGame);

    int prevButton = 0;

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
                singleGame.setFillColor(sf::Color(1,255,244));
                if (prevButton != 2)
                    sound.play();
                menuNum = 2;
                prevButton = 2;
            }
            //Coop Game
            if (sf::IntRect((float)window->getWidth()/ 9 - xProcentUpdate, (float)4*window->getHeight()/9 + 30*yProcentUpdate, 400*xProcentUpdate, 90*yProcentUpdate).contains(
                    sf::Mouse::getPosition(*window->getWindow()))) {
                coopGame.setFillColor(sf::Color(255,160,18));
                if (prevButton != 3)
                    sound.play();
                menuNum = 3;
                prevButton = 3;
            }
            //Exit
            if (sf::IntRect((float)window->getWidth()/ 9 - xProcentUpdate, (float)5*window->getHeight()/9 + 30*yProcentUpdate, 200*xProcentUpdate, 90*yProcentUpdate).contains(
                    sf::Mouse::getPosition(*window->getWindow()))) {
                exitFromGame.setFillColor(sf::Color(235,19,199));
                if (prevButton != 4)
                    sound.play();
                menuNum = 4;
                prevButton = 4;
            }
            //handle Pressed Button
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                //pressed Single Game
                if (menuNum == 2) {
                    singleGame.setCharacterSize(50);
                    window->draw(menuBg);
                    window->draw(singleGame);
                    window->draw(coopGame);
                    window->draw(exitFromGame);
                    window->display();
                    window->clear();
                    usleep(200000);
                    singleGame.setCharacterSize(60);
                    window->draw(menuBg);
                    window->draw(singleGame);
                    window->draw(coopGame);
                    window->draw(exitFromGame);
                    window->display();
                    usleep(100000);
                    window->clear();
                    if (!countDown(window))
                        return(0);
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
                    exitFromGame.setCharacterSize(50);
                    window->draw(menuBg);
                    window->draw(singleGame);
                    window->draw(coopGame);
                    window->draw(exitFromGame);
                    window->display();
                    window->clear();
                    usleep(200000);
                    exitFromGame.setCharacterSize(60);
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

        window->draw(playerName);

        window->draw(singleGame);
        window->draw(coopGame);
        window->draw(exitFromGame);
        window->display();
    }
    return 0;
};


bool countDown(std::shared_ptr<Window> &window)
{
    window->clear();
    sf::Texture countDownBackground;
    countDownBackground.loadFromFile("src/textures/littleRoad.png");
    sf::Sprite countDownBg(countDownBackground);

    countDownBg.setPosition(0,0);

    sf::Font font;
    font.loadFromFile("src/fonts/fontForScore.ttf");
    window->draw(countDownBg);
    window->display();
    sf::Text timeDown;
    timeDown.setFont(font);
    timeDown.setFillColor(sf::Color(255,255,255));

    usleep(500000);
    for (int i = 3; i>=1; i--)
    {
        timeDown.setCharacterSize(30);
        timeDown.setString(toString(i));
        timeDown.setPosition(screenWidth/2 - 35, 1*screenHeight/4 - 35);
        window->draw(countDownBg);
        window->draw(timeDown);
        window->display();
        window->clear();
        timeDown.setCharacterSize(55);
        window->draw(countDownBg);
        window->draw(timeDown);
        window->display();
        window->clear();
        timeDown.setCharacterSize(80);
        window->draw(countDownBg);
        window->draw(timeDown);
        window->display();
        window->clear();
        timeDown.setCharacterSize(120);
        window->draw(countDownBg);
        window->draw(timeDown);
        window->display();
        sleep(1);
    }
    window->clear();
    sf::Text go("Go!", font, 130);
    go.setPosition(screenWidth/2 - 94, screenHeight/3);
    go.setFillColor(sf::Color(115,250,1));
    window->draw(countDownBg);
    window->draw(go);
    window->display();
    sleep(1);
    window->clear();
    return true;
}