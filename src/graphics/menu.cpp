//
// Created by margot on 02.05.2020.
//

#include "graphics/graphic.h"
#include "physics/physics.h"

enum buttons{
    singlPlayB = 1,
    scoreTableB = 2,
    exitB = 0,
    nothingPressed = 10,
};

enum countDown
{
    three = 3,
    one = 1,
};

enum textSizes
{
    beforePress = 60,
    afterPress = 40,
    goSize = 130,
    playerNameSize = 55
};



constexpr pair<float, float> singleGamePos {screenWidth/9, screenHeight/3};
constexpr pair<float, float> scoreInGamePos {screenWidth/9, 4*screenHeight/9};
constexpr pair<float, float> playerNamePos {screenWidth/1.97, screenHeight/30};
constexpr pair<float, float> exitFromGamePos {screenWidth/9, 5*screenHeight/9};
constexpr pair<float, float> timeDownPos {screenWidth/2 - 35, 1*screenHeight/4 - 35};
constexpr pair<float, float> goPos {screenWidth/2 - 94, screenHeight/3};


bool countDown(const shared_ptr<sf::RenderWindow>& window);


void render(const shared_ptr<sf::RenderWindow> &window, const sf::Sprite &menuBg, const sf::Text &playerName,
                            const sf::Text &singleGame,const sf::Text &scoreInGame, const sf::Text &exitFromGame)
{
    window->draw(menuBg);
    window->draw(singleGame);
    window->draw(scoreInGame);
    window->draw(exitFromGame);
    window->draw(playerName);
    window->display();
}

void setSizeForButton(int menuNum, sf::Text &singleGame,
                                sf::Text &scoreInGame, sf::Text &exitFromGame, int size)
{
    if (menuNum == singlPlayB)
        singleGame.setCharacterSize(size);
    else if (menuNum == scoreTableB)
        scoreInGame.setCharacterSize(size);
    else if (menuNum == exitB)
        exitFromGame.setCharacterSize(size);
}

short int buttonIsPressed(const shared_ptr<sf::RenderWindow> &window, int menuNum, const sf::Sprite &menuBg,
                          sf::Text &playerName, sf::Text &singleGame, sf::Text &scoreInGame, sf::Text &exitFromGame)
{
    render(window, menuBg,playerName, singleGame, scoreInGame, exitFromGame);
    usleep(200000);
    window->clear();
    setSizeForButton(menuNum, singleGame, scoreInGame, exitFromGame, afterPress);
    render(window, menuBg,playerName, singleGame, scoreInGame, exitFromGame);
    usleep(100000);
    setSizeForButton(menuNum, singleGame, scoreInGame, exitFromGame, beforePress);
    render(window, menuBg,playerName, singleGame, scoreInGame, exitFromGame);
    window->clear();
    if (menuNum == singlPlayB)
    {
        if (!countDown(window))
            return(exitB);
        return singlPlayB;
    }
    else if (menuNum == scoreTableB)
    {
        return scoreTableB;
    }
    else if (menuNum == exitB)
    {
        return exitB;
    }
    else
        return nothingPressed;
}


void prevButtonDetect(const shared_ptr<sf::RenderWindow>& window, sf::Text &tempText, int &prevButton, int &menuNum, const int &type,const sf::Color &color)
{
    if (isContain(window, tempText))
    {
        tempText.setFillColor(color);
        menuNum = type;
        prevButton = type;
    }
}


void updateView(const shared_ptr<sf::RenderWindow>& window, sf::Text &singleGame,
        sf::Text &scoreInGame, sf::Text &exitFromGame, int &prevButton, int &menuNum)
{
    singleGame.setFillColor(sf::Color::White);
    scoreInGame.setFillColor(sf::Color::White);
    exitFromGame.setFillColor(sf::Color::White);
    menuNum = nothingPressed;

    prevButtonDetect(window, singleGame, prevButton, menuNum,singlPlayB, sf::Color(1,255,244));
    prevButtonDetect(window, scoreInGame, prevButton, menuNum,scoreTableB, sf::Color(255,160,18));
    prevButtonDetect(window, exitFromGame, prevButton, menuNum,exitB, sf::Color(235,19,199));

}

short int displayMenu(const shared_ptr<sf::RenderWindow>& window,const string& name,const std::tuple<vector<string>, vector<int>, vector<int>> &highTable)
{
<<<<<<< HEAD
=======
	window->clear();
    sf::SoundBuffer buffer;
    buffer.loadFromFile("src/sounds/button.ogg");
    sf::Sound sound;
    sound.setBuffer(buffer);

>>>>>>> 877a438623e41a231b460e2698942b9c0cb497c7
    sf::Texture menuBackground;
    menuBackground.loadFromFile("src/textures/bg.png");
    sf::Sprite menuBg(menuBackground);
    int menuNum = exitB;
    menuBg.setPosition(leftAngle,leftAngle);


    sf::Font font;
    font.loadFromFile("src/fonts/fontForScore.ttf");

    sf::Text playerName("Hello," + name+"!", font, playerNameSize), singleGame("Single game", font, beforePress);
    sf::Text scoreInGame("High score", font, beforePress), exitFromGame("Exit", font, beforePress);

    playerName.setFillColor(sf::Color(243,11,109));
    singleGame.setFillColor(sf::Color(255,255,255));
    scoreInGame.setFillColor(sf::Color(255,255,255));
    exitFromGame.setFillColor(sf::Color(255,255,255));
    singleGame.setPosition(singleGamePos.first, singleGamePos.second);
    scoreInGame.setPosition(scoreInGamePos.first, scoreInGamePos.second);
    playerName.setPosition(playerNamePos.first, playerNamePos.second);
    exitFromGame.setPosition(exitFromGamePos.first, exitFromGamePos.second);
    window->draw(playerName);
    window->draw(singleGame);
    window->draw(scoreInGame);
    window->draw(exitFromGame);

    int prevButton = exitB;

    sf::Event event{};
    while (true)
    {
        window->clear();
        if (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
                return exitB;
            }
            updateView(window, singleGame,scoreInGame, exitFromGame, prevButton, menuNum);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                short int buttonPressed = buttonIsPressed(window, menuNum, menuBg,playerName, singleGame, scoreInGame, exitFromGame);
                if (buttonPressed == singlPlayB || buttonPressed == exitB)
                    return buttonPressed;
                else if (buttonPressed == scoreTableB)
				{
                    if (!displayScoreTable(window, highTable))
                        return exitB;
				}
            }
        }
        render(window, menuBg,playerName, singleGame, scoreInGame, exitFromGame);
    }
    return 0;
};

void renderCountDown(const shared_ptr<sf::RenderWindow>& window, const sf::Sprite &countDownBg, const sf::Text &timeDown)
{
    window->draw(countDownBg);
    window->draw(timeDown);
    window->display();
    window->clear();
}

bool countDown(const shared_ptr<sf::RenderWindow>& window)
{
    window->clear();
    sf::Texture countDownBackground;
    countDownBackground.loadFromFile("src/textures/littleRoad.png");
    sf::Sprite countDownBg(countDownBackground);

    countDownBg.setPosition(leftAngle,leftAngle);

    sf::Font font;
    font.loadFromFile("src/fonts/fontForScore.ttf");
    window->draw(countDownBg);
    window->display();
    sf::Text timeDown;
    timeDown.setFont(font);
    timeDown.setFillColor(sf::Color::White);

    usleep(500000);
    for (int i = three; i>=one; i--)
    {
        timeDown.setCharacterSize(30);
        timeDown.setString(toString(i));
        timeDown.setPosition(timeDownPos.first, timeDownPos.second);
        renderCountDown(window, countDownBg, timeDown);
        timeDown.setCharacterSize(55);
        renderCountDown(window, countDownBg, timeDown);
        timeDown.setCharacterSize(80);
        renderCountDown(window, countDownBg, timeDown);
        timeDown.setCharacterSize(120);
        renderCountDown(window, countDownBg, timeDown);
        sleep(1);
    }
    window->clear();
    sf::Text go("Go!", font, goSize);
    go.setPosition(goPos.first, goPos.second);
    go.setFillColor(sf::Color(115,250,1));
    window->draw(countDownBg);
    window->draw(go);
    window->display();
    sleep(1);
    window->clear();
    return true;
}