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
    setSizeForButton(menuNum, singleGame, scoreInGame, exitFromGame, 40);
    render(window, menuBg,playerName, singleGame, scoreInGame, exitFromGame);
    usleep(100000);
    setSizeForButton(menuNum, singleGame, scoreInGame, exitFromGame, 60);
    render(window, menuBg,playerName, singleGame, scoreInGame, exitFromGame);
    window->clear();
    if (menuNum == singlPlayB)
    {
        if (!countDown(window))
            return(0);
        return 1;
    }
    else if (menuNum == scoreTableB)
    {
        return 2;
    }
    else if (menuNum == exitB)
    {
        return 0;
    }
    else
        return nothingPressed;
}



void updateView(const shared_ptr<sf::RenderWindow>& window, sf::Sound sound, sf::Text &singleGame,
        sf::Text &scoreInGame, sf::Text &exitFromGame, int &prevButton, int &menuNum)
{
    singleGame.setFillColor(sf::Color(255,255,255));
    scoreInGame.setFillColor(sf::Color(255,255,255));
    exitFromGame.setFillColor(sf::Color(255,255,255));
    menuNum = nothingPressed;

    if (isContain(window, singleGame)) {
        singleGame.setFillColor(sf::Color(1,255,244));
        if (prevButton != singlPlayB) {
            sound.play();
        }
        menuNum = singlPlayB;
        prevButton = singlPlayB;
    }
        //Coop Game
    if (isContain(window, scoreInGame)) {
        scoreInGame.setFillColor(sf::Color(255,160,18));
        if (prevButton != scoreTableB) {
            sound.setPlayingOffset(sf::seconds(2.f));
        }
        menuNum = scoreTableB;
        prevButton = scoreTableB;
    }
        //Exit
    if (isContain(window, exitFromGame)) {
        exitFromGame.setFillColor(sf::Color(235,19,199));
        if (prevButton != exitB) {
            sound.play();
        }
        menuNum = exitB;
        prevButton = exitB;
    }
}

short int displayScoreTable(const shared_ptr<sf::RenderWindow>& window, const std::tuple<vector<string>, vector<int>, vector<int>> &highTable)
{
    sf::Font font;
    font.loadFromFile("src/fonts/fontForScore.ttf");



    sf::Texture menuBackground;
    menuBackground.loadFromFile("src/textures/scoreTable.png");
    sf::Sprite menuBg(menuBackground);
    menuBg.setPosition(0,0);
    pair<float, float> point(screenWidth/4.15, screenHeight/3.1);


    sf::Text header("Place   Score   Name", font, 52);
    header.setFillColor(sf::Color(0,183,240));
    header.setPosition(screenWidth/4.1, screenHeight/4.7);

    sf::Text goBack("Back", font, 50);
    goBack.setPosition(screenWidth/2.25, screenHeight/1.12);

    std::vector<std::tuple<sf::Text, sf::Text>> scoreTable;

    for (int i = 0; i < std::get<0>(highTable).size(); i++)
    {
        sf::Text tempScore(toString(i+1)+"'th"+"       " + toString(std::get<1>(highTable)[i]), font, 40) ;
        sf::Text nickname (toString(std::get<0>(highTable)[i]) , font, 40);
        tempScore.setPosition(point.first, point.second);
        nickname.setPosition(point.first + 485, point.second);
        tempScore.setFillColor(sf::Color(255,255,255));
        nickname.setFillColor(sf::Color(255,255,255));
        scoreTable.emplace_back(tempScore, nickname);
        point.second += 55;
    }

    bool isPressed = false;
    sf::Event event{};
    while (!isPressed)
    {
        if (window->pollEvent(event))
        {
            goBack.setFillColor(sf::Color(255,162,45));
            if (event.type == sf::Event::Closed)
            {
                window->close();
                return 0;
            }
            if (isContain(window, goBack))
            {
                goBack.setFillColor(sf::Color::Red);
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isContain(window, goBack))
            {
                isPressed = true;
                goBack.setCharacterSize(40);
            }
        }

        window->draw(menuBg);
        window->draw(header);
        window->draw(goBack);
        for (auto & curScore : scoreTable) {
            window->draw(std::get<0>(curScore));
            window->draw(std::get<1>(curScore));
        }
        window->display();
        window->clear();
    }
    return 1;
}

short int displayMenu(const shared_ptr<sf::RenderWindow>& window,const string& name,const std::tuple<vector<string>, vector<int>, vector<int>> &highTable)
{
    sf::SoundBuffer buffer;
    buffer.loadFromFile("src/sounds/button.ogg");
    sf::Sound sound;
    sound.setBuffer(buffer);

    sf::Texture menuBackground;
    menuBackground.loadFromFile("src/textures/bg.png");
    sf::Sprite menuBg(menuBackground);
    int menuNum = 0;
    menuBg.setPosition(0,0);


    sf::Font font;
    font.loadFromFile("src/fonts/fontForScore.ttf");

    sf::Text playerName("Hello," + name+"!", font, 65), singleGame("Single game", font, 60);
    sf::Text scoreInGame("High score", font, 60), exitFromGame("Exit", font, 60);

    playerName.setFillColor(sf::Color::Yellow);
    singleGame.setFillColor(sf::Color(255,255,255));
    scoreInGame.setFillColor(sf::Color(255,255,255));
    exitFromGame.setFillColor(sf::Color(255,255,255));
    singleGame.setPosition(screenWidth/9, screenHeight/3);
    scoreInGame.setPosition(screenWidth/9, 4*screenHeight/9);
    playerName.setPosition(11*screenWidth/18, screenHeight/18);
    exitFromGame.setPosition(screenWidth/9, 5*screenHeight/9);
    window->draw(playerName);
    window->draw(singleGame);
    window->draw(scoreInGame);
    window->draw(exitFromGame);

    int prevButton = 0;

    sf::Event event{};
    while (true)
    {
        window->clear();
        if (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
                return 0;
            }
            updateView(window, sound, singleGame,scoreInGame, exitFromGame, prevButton, menuNum);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                short int buttonPressed = buttonIsPressed(window, menuNum, menuBg,playerName, singleGame, scoreInGame, exitFromGame);
                if (buttonPressed == singlPlayB || buttonPressed == exitB)
                    return buttonPressed;
                else if (buttonPressed == scoreTableB)
                    if (!displayScoreTable(window, highTable))
                        return 0;
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