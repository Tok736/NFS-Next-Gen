//
// Created by margot on 02.05.2020.
//

#include "graphic.h"

void Clock::restart()
{
    clock_.restart();
}

float Clock::getClockMicro() {
    return clock_.getElapsedTime().asMicroseconds();
}


float Clock::getClockSec() {
    return clock_.getElapsedTime().asSeconds();
}


void Window::createRenderWindow(Window *miniEngine, float width, float height, const std::string &title) {
    miniEngine->renderWindow_ = new sf::RenderWindow(sf::VideoMode((unsigned int)width, (unsigned int)height), title);
    miniEngine->setHeight(height);
    miniEngine->setWidth(width);
}

void Window::setWidth(float width) {
    width_ = width;
}

void Window::setHeight(float height) {
    height_ = height;
}

bool Window::isOpen() {
    return renderWindow_->isOpen();
}

void Window::handleEvents(std::vector<int> &actions) {
    sf::Event event{};
    if (renderWindow_->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            actions.push_back(endOfTheGame);
            return ;
        }
        if (event.type == sf::Event::KeyPressed)
        {
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


void Window::render(std::vector<Car> cars, std::vector<Obstruction> roadAndObstcl) {
    renderWindow_->clear();

//    sf::Texture roadTexture;

    sf::RectangleShape rectangle(sf::Vector2f(120, 50));
    rectangle.setSize(sf::Vector2f(10, 100));
    for (int i=10; i<height_; i+=150)
    {
        rectangle.setPosition(width_/2, i);
        renderWindow_->draw(rectangle);
    }

    for (auto & car : cars)
    {
        sf::Texture carTexture;
        carTexture.loadFromFile("/home/margot/Desktop/car.jpg");
        sf::Sprite carSprite(carTexture);
        carSprite.setPosition((float)car.getX(), (float)car.getY());
        renderWindow_->draw(carSprite);
    }


}

void Window::display() {
    renderWindow_->display();
}

void Window::close() {
    renderWindow_->close();
}