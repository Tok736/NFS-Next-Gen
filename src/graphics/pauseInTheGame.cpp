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
    exitFromGameB = 0
};

enum textSizes
{
    beforePress = 60,
    afterPress = 40,
    scoreButtonSize = 70,
};

constexpr pair<float, float> scorePos {screenWidth/4, screenHeight/10};
constexpr pair<float, float> continueGamePos {screenWidth/9, screenHeight/3};
constexpr pair<float, float> startAgainPos {screenWidth/9, 4*screenHeight/9};
constexpr pair<float, float> exitFromGamePos {screenWidth/9, 5*screenHeight/9};


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

void prevButtonDetect(const shared_ptr<sf::RenderWindow>& window, sf::Text &tempText, int &menuNum, const int &type,const sf::Color &color)
{
    if (isContain(window, tempText))
    {
        tempText.setFillColor(color);
        menuNum = type;
    }
}

void updatePauseView(const shared_ptr<sf::RenderWindow>& window, sf::Text &continueGame,
                sf::Text &startAgain, sf::Text &exitFromGame, int &menuNum)
{
    continueGame.setFillColor(sf::Color::White);
    startAgain.setFillColor(sf::Color::White);
    exitFromGame.setFillColor(sf::Color::White);

    prevButtonDetect(window, continueGame,  menuNum,continueB, sf::Color(1,255,244));
    prevButtonDetect(window, startAgain,  menuNum,restartB, sf::Color(235, 230, 9));
    prevButtonDetect(window, exitFromGame,  menuNum,exitB, sf::Color(82,43,255));
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
    setSizeForButtonPause(menuNum, continueGame, startAgain, exitFromGame, afterPress);
    renderPause(window, menuBg,continueGame, startAgain, exitFromGame);
    usleep(100000);
    setSizeForButtonPause(menuNum, continueGame, startAgain, exitFromGame, beforePress);
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
    int start = exitFromGameB;
    menuBg.setPosition(leftAngle,leftAngle);


    sf::Font font;
    font.loadFromFile("src/fonts/fontForScore.ttf");
    std::string scoreString("Your score: " + to_string(timeInGame) + "!");
    sf::Text continueGame("Continue", font, beforePress), startAgain("Start again", font, beforePress);
    sf::Text exitFromGame("Back to menu", font, beforePress), score(scoreString, font, scoreButtonSize);
    score.setFillColor(sf::Color(33,255,130));
    continueGame.setFillColor(sf::Color::White);
    startAgain.setFillColor(sf::Color::White);
    exitFromGame.setFillColor(sf::Color::White);
    score.setPosition(scorePos.first, scorePos.second);
    continueGame.setPosition(continueGamePos.first, continueGamePos.second);
    startAgain.setPosition(startAgainPos.first, startAgainPos.second);
    exitFromGame.setPosition(exitFromGamePos.first, exitFromGamePos.second);
    window->draw(score);
    window->draw(continueGame);
    window->draw(startAgain);
    window->draw(exitFromGame);

    sf::Event event;
    while (!start)
    {
        score.setFillColor(sf::Color(33,255,130));
        menuNum = exitFromGameB;
        window->clear();
        if (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
                return exitFromGameB;
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