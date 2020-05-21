//
// Created by margot on 11.05.2020.
//

#include "graphics/graphic.h"
#include "physics/physics.h"

enum buttons{
    continueB = 2,
    restartB = 3,
    exitB = 4,
    nothingPressed = 10,
};




short int pauseWindow(const shared_ptr<sf::RenderWindow>& window,const int &timeInGame)
{
    sf::Texture menuBackground;
    menuBackground.loadFromFile("src/textures/bgPause.png");
    sf::Sprite menuBg(menuBackground);
    int menuNum = 0;
    int start = 0;
    menuBg.setPosition(0,0);


    sf::Font font;
    font.loadFromFile("src/fonts/fontForScore.ttf");
    std::string scoreString("Your score: " + toString(timeInGame) + "!");
    sf::Text continueGame("Continue", font, 60), startAgain("Start again", font, 60), exitFromGame("Exit", font, 60), score(scoreString, font, 70);
    score.setFillColor(sf::Color(33,255,130));
    continueGame.setFillColor(sf::Color(255,255,255));
    startAgain.setFillColor(sf::Color(255,255,255));
    exitFromGame.setFillColor(sf::Color(255,255,255));
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
        score.setFillColor(sf::Color(33,255,130));
        continueGame.setFillColor(sf::Color(255,255,255));
        startAgain.setFillColor(sf::Color(255,255,255));
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
            //continue Game
            if (isContain(window, continueGame))
            {
                continueGame.setFillColor(sf::Color(1,255,244));
                menuNum = continueB;
            }
            //restart Game
            if (isContain(window, startAgain)) {
                startAgain.setFillColor(sf::Color(235, 230, 9));
                menuNum = restartB;
            }
            //Exit
            if (isContain(window, exitFromGame)) {
                exitFromGame.setFillColor(sf::Color(82,43,255));
                menuNum = exitB;
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