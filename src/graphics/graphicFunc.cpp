//
// Created by margot on 02.05.2020.
//

#include <sstream>
#include "graphics/graphic.h"
#include "phisics/physics.h"

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
    if (renderWindow_->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            actions.push_back(endOfTheGame);
            return;
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Right)
                actions.push_back(myRight);
            if (event.key.code == sf::Keyboard::Left)
                actions.push_back(myLeft);
            if (event.key.code == sf::Keyboard::Up)
                actions.push_back(myUp);
            if (event.key.code == sf::Keyboard::Down)
                actions.push_back(myDown);
        }
    }
}

template <typename T>
std::string toString(T val)
{
    std::ostringstream oss;
    oss<<val;
    return oss.str();
}


void Window::render(std::vector<Car> &cars,  std::vector<Obstruction> &roadElements, int &actions, int &timeInGame) {
    renderWindow_->clear();
    sf::Texture roadTexture1, roadTexture2, obstruct;
    roadTexture1.loadFromFile("src/textures/littleroad.jpg");
    roadTexture2.loadFromFile("src/textures/littleroad.jpg");
    obstruct.loadFromFile("src/textures/rock2-min.png");
    sf::Sprite roadSprite1(roadTexture1);
    sf::Sprite roadSprite2(roadTexture2);
    sf::Sprite roadObstract(obstruct);

    if (roadElements.size() >= 2 ) {
        roadObstract.setPosition((float) roadElements[2].getX(), (float) roadElements[2].getY());
        roadSprite1.setPosition(0, (float) roadElements[0].getY());
        roadSprite2.setPosition(0, (float) roadElements[1].getY());
        renderWindow_->draw(roadSprite1);
        renderWindow_->draw(roadSprite2);
        renderWindow_->draw(roadObstract);
    }
    for (auto &car : cars) {
        sf::Texture carTexture;
        if (actions != -1)
        {
            if (actions == myUp)
                carTexture.loadFromFile("src/textures/Car_1.png");
            else if (actions == myDown)
                carTexture.loadFromFile("src/textures/Car_0.png");
            else if (actions == myLeft)
                carTexture.loadFromFile("src/textures/Car_4.png");
            else if (actions == myRight)
                carTexture.loadFromFile("src/textures/Car_6.png");
        }
        else
            carTexture.loadFromFile("src/textures/Car_0.png");
        sf::Sprite carSprite(carTexture);
        carSprite.setPosition((float) car.getX(), (float) car.getY());
        renderWindow_->draw(carSprite);
    }

    sf::RectangleShape scoreShape(sf::Vector2f(screenWidth/3 - 20, screenHeight/10));
    scoreShape.move(2*screenWidth/3+5, 10);
    scoreShape.setFillColor(sf::Color(0,0,0,50));
    renderWindow_->draw(scoreShape);
    sf::Font font;
    font.loadFromFile("src/fonts/fontForScore.ttf");
    sf::Text score("", font, 20);
    score.setFillColor(sf::Color(255,255,255));
    score.setString("Score: " + toString(timeInGame));
    score.setPosition(2*screenWidth/3+5, screenHeight/20);
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

