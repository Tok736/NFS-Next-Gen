//
// Created by margot on 02.05.2020.
//


#include "graphics/graphic.h"
#include "physics/physics.h"

enum obstrectsCoord
{
    obstractX = 56,
    obstractY = 56,
};

enum carCoord{
    carX = carWidth/2,
    carY = 0,
};

enum id{
    roadId = 0,
    firstCarId = 1,
    lastCarId = 9,
    noId = -1,
};


/////////////////////                    CLOCK            //////////////////////////////////////////

void Clock::restart() {
    clock_.restart();
}


float Clock::getClockMicro() {
    return clock_.getElapsedTime().asMicroseconds();
}


float Clock::getClockSec() {
    return clock_.getElapsedTime().asSeconds();
}


/////////////////////                    WINDOW            //////////////////////////////////////////

void Window::createRenderWindow(shared_ptr<Window> miniEngine, unsigned int width, unsigned int height, const std::string &title) {
    auto newWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title, sf::Style::Fullscreen);
    miniEngine->renderWindow_= newWindow;
    miniEngine->setHeight(height);
    miniEngine->setWidth(width);

}

void Window::setWidth(unsigned int width) {
    width_ = width;
}

void Window::setHeight(unsigned int height) {
    height_ = height;
}

bool Window::isOpen() {
    return renderWindow_->isOpen();
}

void Window::handleEvents(std::vector<int> &actions) {
    sf::Event event{};
    while (renderWindow_->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            actions.push_back(endOfTheGame);
            return;
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Right)
                actions.push_back(myRight);
            if (event.key.code == sf::Keyboard::Left)
                actions.push_back(myLeft);
            if (event.key.code == sf::Keyboard::Up)
                actions.push_back(myUp);
            if (event.key.code == sf::Keyboard::Down)
                actions.push_back(myDown);
            if (event.key.code == sf::Keyboard::Escape)
                actions.push_back(pauseOfTheGame);
        }
        else break;
    }
}


void Window::createTextures(std::vector<shared_ptr<IGameElement>> &roadAndObstcl)
{
    for (auto & roadElem : roadAndObstcl)
    {
        sf::Texture tempTexture;
        std::vector<sf::Texture> tempVectorOfTextures;
        int id = roadElem->getId();
        vector<std:: string> typeOfObstacle;
        if (id == roadId)
            typeOfObstacle.emplace_back("littleRoad");
        else if (id >=firstCarId && id <= lastCarId)
        {
            for (int i=0; i<4; i++) //numbers of cars conditions (left,up,right,down)
                typeOfObstacle.emplace_back("CarAction_" + toString(id)+toString(i));
        }
        else{
            typeOfObstacle.emplace_back("obstruction" + toString(roadElem->getId()));
        }

        for (auto & iter : typeOfObstacle)
        {
            tempTexture.loadFromFile("src/textures/" +iter +".png");
            tempVectorOfTextures.push_back(tempTexture);
        }
        mapOfRextures.insert(std::pair<int, std::vector<sf::Texture>>(id, tempVectorOfTextures));
    }
}

void Window::render(std::vector<shared_ptr<IGameElement>> &roadElements, int &actions, int &timeInGame) {
    renderWindow_->clear();

    sf::Font font;
    font.loadFromFile("src/fonts/fontForScore.ttf");
    sf::Text hp("Health: ", font, 30);
    hp.setPosition(screenWidth/28.24,screenHeight/21.95);

    for (auto & roadElement : roadElements)
    {
        if (roadElement->getId() == roadId)
        {
            sf::Sprite roadSprite1(mapOfRextures.find(roadElements[0]->getId())->second[0]);
            sf::Sprite roadSprite2(mapOfRextures.find(roadElements[1]->getId())->second[0]);
            roadSprite1.setPosition(0, (float) roadElements[0]->getY());
            roadSprite2.setPosition(0, (float) roadElements[1]->getY());
            renderWindow_->draw(roadSprite1);
            renderWindow_->draw(roadSprite2);
        }
        else if (roadElement->getId() >= firstCarId && roadElement->getId() <= lastCarId)
        {
            sf::Sprite carSprite;
            if (actions != myNoAction)
            {
                if (actions == myUp)
                    carSprite.setTexture(mapOfRextures.find(roadElement->getId())->second[1]);
                else if (actions == myDown)
                    carSprite.setTexture(mapOfRextures.find(roadElement->getId())->second[0]);
                else if (actions == myLeft)
                    carSprite.setTexture(mapOfRextures.find(roadElement->getId())->second[2]);
                else if (actions == myRight)
                    carSprite.setTexture(mapOfRextures.find(roadElement->getId())->second[3]);
            }
            else
                carSprite.setTexture(mapOfRextures.find(roadElement->getId())->second[0]);

            hp.setString("Health: " + toString(roadElement->getHealthCount()) + "%");
            carSprite.setOrigin(carX, carY);
            carSprite.setRotation((float) roadElement->getAngle());
            carSprite.setPosition(roadElement->getX(), roadElement->getY());
            renderWindow_->draw(carSprite);

        }
        else if (roadElement->getId() != noId) {
            sf::Sprite roadObstract(mapOfRextures.find(roadElement->getId())->second[0]);
            roadObstract.setPosition((float) roadElement->getX() - obstractX, (float) roadElement->getY() - obstractY);
            renderWindow_->draw(roadObstract);
        }
    }


    sf::RectangleShape scoreShape(sf::Vector2f(screenWidth/3.683, screenHeight/9.47));
    sf::RectangleShape hpShape(sf::Vector2f(screenWidth/3.683, screenHeight/9.47));
    scoreShape.move(screenWidth/1.37, screenHeight/90.0);
    hpShape.move(0,screenHeight/90.0);
    scoreShape.setFillColor(sf::Color(0,0,0,50));
    hpShape.setFillColor(sf::Color(0,0,0,50));
    renderWindow_->draw(scoreShape);
    renderWindow_->draw(hpShape);
    renderWindow_->draw(hp);

    sf::Text score("", font, 30);
    score.setFillColor(sf::Color(255,255,255));
    score.setString("Score: " + toString<int>(timeInGame));
    score.setPosition(screenWidth/1.28, screenHeight/21.95);


    renderWindow_->draw(score);
}

void Window::display() {
    renderWindow_->display();
}

void Window::close() {
    renderWindow_->close();
}

void Window::clear() {
    renderWindow_->clear();
}


bool Window::pollEvent(sf::Event& event) {
    renderWindow_->pollEvent(event);
    return true;
}

shared_ptr<sf::RenderWindow> Window::getRenderWindow() {
    return renderWindow_;
}


bool isContain(const shared_ptr<sf::RenderWindow>& window, const sf::Text& temp)
{
    return (temp.getGlobalBounds()).contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
}