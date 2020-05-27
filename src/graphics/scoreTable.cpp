//
// Created by margot on 24.05.2020.
//

#include "graphics/graphic.h"
#include "physics/physics.h"


enum offset
{
    nicknameOffset = 485,
    interval = 55,
};

enum button
{
    exitB = 0,
    backB = 1
};

enum textSizes
{
    headerSize = 52,
    goBackSize = 50,
    stringInScore = 40,
};

constexpr pair<float, float> headerPos {screenWidth/4.1, screenHeight/4.7};
constexpr pair<float, float> pointPos(screenWidth/4.15, screenHeight/3.1);
constexpr pair<float, float> goBackPos {screenWidth/2.25, screenHeight/1.12};


short int displayScoreTable(const shared_ptr<sf::RenderWindow>& window, const std::tuple<vector<string>, vector<int>, vector<int>> &highTable)
{
    sf::Font font;
    font.loadFromFile("src/fonts/fontForScore.ttf");



    sf::Texture menuBackground;
    menuBackground.loadFromFile("src/textures/scoreTable.png");
    sf::Sprite menuBg(menuBackground);
    menuBg.setPosition(leftAngle,leftAngle);
    pair<float, float> point(pointPos.first, pointPos.second);


    sf::Text header("Place   Score   Name", font, headerSize);
    header.setFillColor(sf::Color(0,183,240));
    header.setPosition(headerPos.first, headerPos.second);

    sf::Text goBack("Back", font, goBackSize);
    goBack.setPosition(goBackPos.first, goBackPos.second);

    std::vector<std::tuple<sf::Text, sf::Text>> scoreTable;

    for (int i = 0; i < std::get<0>(highTable).size(); i++)
    {
        sf::Text tempScore(toString(i+1)+"'th"+"       " + toString(std::get<1>(highTable)[i]), font, stringInScore) ;
        sf::Text nickname (toString(std::get<0>(highTable)[i]) , font, stringInScore);
        tempScore.setPosition(point.first, point.second);
        nickname.setPosition(point.first + nicknameOffset, point.second);
        tempScore.setFillColor(sf::Color::White);
        nickname.setFillColor(sf::Color::White);
        scoreTable.emplace_back(tempScore, nickname);
        point.second += interval;
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
                return exitB;
            }
            if (isContain(window, goBack))
            {
                goBack.setFillColor(sf::Color::Red);
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isContain(window, goBack))
            {
                isPressed = true;
                goBack.setCharacterSize(stringInScore);
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
    return backB;
}