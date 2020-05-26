//
// Created by margot on 11.05.2020.
//

#include "graphics/graphic.h"
#include "physics/physics.h"

enum buttons{
    continueB = 3,
    restartB = 1,
    exitB = 2,
    nothingPressed = 10,
};

void setSizeForButtonPause(int menuNum, sf::Text &singleGame,
                      sf::Text &scoreInGame, sf::Text &exitFromGame, int size)
{
    if (menuNum == continueB)
        singleGame.setCharacterSize(size);
    else if (menuNum == restartB)
        scoreInGame.setCharacterSize(size);
    else if (menuNum == exitB)
        exitFromGame.setCharacterSize(size);
}

void updatePauseView(const shared_ptr<sf::RenderWindow>& window, sf::Text &continueGame,
                sf::Text &startAgain, sf::Text &exitFromGame, int &menuNum)
{
    continueGame.setFillColor(sf::Color(255,255,255));
    startAgain.setFillColor(sf::Color(255,255,255));
    exitFromGame.setFillColor(sf::Color(255,255,255));

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
}

void renderPause(const shared_ptr<sf::RenderWindow> &window, const sf::Sprite &menuBg,
                 const sf::Text &continueGame, const sf::Text &startAgain, const sf::Text &exitFromGame)
{
    window->draw(menuBg);
    window->draw(continueGame);
    window->draw(startAgain);
    window->draw(exitFromGame);
    window->display();
}

short int buttonIsPressed(const shared_ptr<sf::RenderWindow> &window, int menuNum, const sf::Sprite &menuBg,
                          sf::Text &continueGame, sf::Text &startAgain, sf::Text &exitFromGame)
{
    renderPause(window, menuBg, continueGame, startAgain, exitFromGame);
    usleep(200000);
    window->clear();
    setSizeForButtonPause(menuNum, continueGame, startAgain, exitFromGame, 40);
    renderPause(window, menuBg,continueGame, startAgain, exitFromGame);
    usleep(100000);
    setSizeForButtonPause(menuNum, continueGame, startAgain, exitFromGame, 60);
    renderPause(window, menuBg,continueGame, startAgain, exitFromGame);
    window->clear();
    if (menuNum == continueB)
    {
        return continueB;
    }
    else if (menuNum == restartB)
    {
        return restartB;
    }
    else if (menuNum == exitB)
    {
        return exitB;
    }
    else
        return nothingPressed;
}



short int pauseWindow(const shared_ptr<sf::RenderWindow>& window,const int &timeInGame)
{
    sf::Texture menuBackground;
    menuBackground.loadFromFile("src/textures/bgPause.png");
    sf::Sprite menuBg(menuBackground);
    int menuNum = nothingPressed;
    int start = 0;
    menuBg.setPosition(0,0);


    sf::Font font;
    font.loadFromFile("src/fonts/fontForScore.ttf");
    std::string scoreString("Your score: " + toString(timeInGame) + "!");
    sf::Text continueGame("Continue", font, 60), startAgain("Start again", font, 60), exitFromGame("Back to menu", font, 60), score(scoreString, font, 70);
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
        menuNum = 0;
        window->clear();
        if (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
                return 0;
            }
            updatePauseView(window, continueGame, startAgain, exitFromGame, menuNum);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                short int buttonPressed = buttonIsPressed(window, menuNum, menuBg,continueGame, startAgain, exitFromGame);
                if (buttonPressed != nothingPressed)
                    return buttonPressed;
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