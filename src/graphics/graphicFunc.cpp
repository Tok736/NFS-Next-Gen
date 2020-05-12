//
// Created by margot on 02.05.2020.
//


#include "graphics/graphic.h"
#include "physics/physics.h"

#define obstractX 56
#define obstractY 56
#define carX carHeight/2
#define carY carLength/2

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
    shared_ptr<sf::RenderWindow> newWindow(new sf::RenderWindow(sf::VideoMode(width, height), title));
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
        if (roadElem->getId()== 0)
        {
            tempTexture.loadFromFile("src/textures/littleRoad.png");
            tempVectorOfTextures.push_back(tempTexture);
        }
        else if (roadElem->getId() >=1 && roadElem->getId() <= 9)
        {
            for (int i=0; i<4; i++)
            {
                tempTexture.loadFromFile("src/textures/CarAction_"+toString(i)+".png");
                tempVectorOfTextures.push_back(tempTexture);
            }
        }
        else{
            tempTexture.loadFromFile("src/textures/obstruction" + toString(roadElem->getId())+ ".png");
            tempVectorOfTextures.push_back(tempTexture);
        }
        mapOfRextures.insert(std::pair<int, std::vector<sf::Texture>>(roadElem->getId(), tempVectorOfTextures));
    }
}

void Window::render(std::vector<shared_ptr<IGameElement>> &roadElements, int &actions, int &timeInGame) {
    renderWindow_->clear();


    for (auto & roadElement : roadElements)
    {
        if (roadElement->getId() == 0)
        {
            sf::Sprite roadSprite1(mapOfRextures.find(roadElements[0]->getId())->second[0]);
            sf::Sprite roadSprite2(mapOfRextures.find(roadElements[1]->getId())->second[0]);
            roadSprite1.setPosition(0, (float) roadElements[0]->getY());
            roadSprite2.setPosition(0, (float) roadElements[1]->getY());
            renderWindow_->draw(roadSprite1);
            renderWindow_->draw(roadSprite2);
        }
        else if (roadElement->getId() >= 1 && roadElement->getId() <= 9)
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

            carSprite.setPosition((float) roadElement->getX() - carX, (float) roadElement->getY() + carY);
            renderWindow_->draw(carSprite);
        }
        else {
            sf::Sprite roadObstract(mapOfRextures.find(roadElement->getId())->second[0]);
            roadObstract.setPosition((float) roadElement->getX() - obstractX, (float) roadElement->getY() - obstractY);
            renderWindow_->draw(roadObstract);
        }
    }


    sf::RectangleShape scoreShape(sf::Vector2f(screenWidth/3 - 20, screenHeight/10));
    scoreShape.move(35*screenWidth/48, 10);
    scoreShape.setFillColor(sf::Color(0,0,0,50));
    renderWindow_->draw(scoreShape);
    sf::Font font;
    font.loadFromFile("src/fonts/fontForScore.ttf");
    sf::Text score("", font, 20);
    score.setFillColor(sf::Color(255,255,255));
    score.setString("Score: " + toString<int>(timeInGame));
    score.setPosition(35*screenWidth/48, screenHeight/20);
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

void Window::draw(sf::Sprite &toDraw) {
    renderWindow_->draw(toDraw);
}

shared_ptr<sf::RenderWindow> Window::getWindow() {
    return renderWindow_;
}

bool Window::pollEvent(sf::Event& event) {
    renderWindow_->pollEvent(event);
    return true;
}

shared_ptr<sf::RenderWindow> Window::getRenderWindow() {
    return renderWindow_;
}

unsigned int Window::getWidth() const {
    return width_;
}

unsigned int Window::getHeight() const {
    return height_;
}

void Window::draw(sf::Text &toDraw) {
    renderWindow_->draw(toDraw);
}

