//
// Created by margot on 24.05.2020.
//

#include "graphics/graphic.h"
#include "physics/physics.h"


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
    header.setColor(sf::Color(0,183,240));
    header.setPosition(screenWidth/4.1, screenHeight/4.7);

    sf::Text goBack("Back", font, 50);
    goBack.setPosition(screenWidth/2.25, screenHeight/1.12);

    std::vector<std::tuple<sf::Text, sf::Text>> scoreTable;

    for (unsigned int i = 0; i < std::get<0>(highTable).size(); i++)
    {
        sf::Text tempScore(toString(i+1)+"'th"+"       " + toString(std::get<1>(highTable)[i]), font, 40) ;
        sf::Text nickname (toString(std::get<0>(highTable)[i]) , font, 40);
        tempScore.setPosition(point.first, point.second);
        nickname.setPosition(point.first + 485, point.second);
        tempScore.setColor(sf::Color(255,255,255));
        nickname.setColor(sf::Color(255,255,255));
        scoreTable.emplace_back(tempScore, nickname);
        point.second += 55;
    }

    bool isPressed = false;
    sf::Event event{};
    while (!isPressed)
    {
        if (window->pollEvent(event))
        {
            goBack.setColor(sf::Color(255,162,45));
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