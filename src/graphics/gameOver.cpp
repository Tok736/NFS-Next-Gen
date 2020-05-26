//
// Created by margot on 26.05.2020.
//

//
// Created by margot on 11.05.2020.
//

#include "graphics/graphic.h"
#include "physics/physics.h"

enum buttons{
    exitB = 0,
    nothingPressed = 10,
};

void renderPause(const shared_ptr<sf::RenderWindow> &window, const sf::Sprite &menuBg, const sf::Text &exitFromGame)
{
    window->draw(menuBg);
    window->draw(exitFromGame);
    window->display();
}

void visiblePress(const shared_ptr<sf::RenderWindow> &window,const sf::Sprite &menuBg, sf::Text &exitFromGame,const int &size, const unsigned int &sleep)
{
    renderPause(window, menuBg, exitFromGame);
    usleep(sleep);
    window->clear();
    exitFromGame.setCharacterSize(size);
}

void updatePauseView(const shared_ptr<sf::RenderWindow>& window, sf::Text &exitFromGame, int &menuNum)
{

    exitFromGame.setFillColor(sf::Color(255,175,103));

    //Exit
    if (isContain(window, exitFromGame)) {
        exitFromGame.setFillColor(sf::Color(207,96,128));
        menuNum = exitB;
    }
}


short int buttonIsPressed(const shared_ptr<sf::RenderWindow> &window, int menuNum, const sf::Sprite &menuBg, sf::Text &exitFromGame)
{
    visiblePress(window, menuBg, exitFromGame, 40, 200000);
    visiblePress(window, menuBg, exitFromGame, 60, 100000);
    window->clear();

    if (menuNum == exitB)
    {
        return exitB;
    }
    else
        return nothingPressed;
}



short int displayGameOver(const shared_ptr<sf::RenderWindow>& window,const int &timeInGame)
{
    sf::Texture menuBackground;
    menuBackground.loadFromFile("src/textures/gameOver.png");
    sf::Sprite menuBg(menuBackground);
    int menuNum = nothingPressed;
    int start = 0;
    menuBg.setPosition(0,0);


    sf::Font font;
    font.loadFromFile("src/fonts/fontForScore.ttf");
    std::string scoreString("Your score: " + toString(timeInGame) + "!");
    sf::Text exitFromGame("Back to menu", font, 83), score(scoreString, font, 75);
    score.setFillColor(sf::Color(234,119,120));

    exitFromGame.setFillColor(sf::Color(255,175,103));
    score.setPosition(screenWidth/3.55, screenHeight/24.66);

    exitFromGame.setPosition(screenWidth/3.3, screenHeight/1.2);
    window->draw(score);

    window->draw(exitFromGame);

    sf::Event event;
    while (!start)
    {
        menuNum = 0;
        window->clear();
        if (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
                return 0;
            }
            updatePauseView(window, exitFromGame, menuNum);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                short int buttonPressed = buttonIsPressed(window, menuNum, menuBg,exitFromGame);
                if (buttonPressed != nothingPressed)
                    return buttonPressed;
            }
        }
        window->draw(menuBg);
        window->draw(score);
        window->draw(exitFromGame);
        window->display();
    }
    return 0;
}