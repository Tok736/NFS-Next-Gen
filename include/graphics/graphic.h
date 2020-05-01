//
// Created by margot on 15.04.2020.
//

#ifndef NFS_NEXT_GEN_UTILS_H
#define NFS_NEXT_GEN_UTILS_H

#include <SFML/Graphics.hpp>
#include <string>
#include "testGameElement.h"

class Event;

class Window{
public:
    Window(){};
    ~Window(){};

    static void createRenderWindow(Window *miniEngine, float width, float height, const std::string &title);

//    sf::RenderWindow *getRenderWindow();
    float getWidth();
    float getHeight();
    void setWidth(float width);
    void setHeight(float height);
    sf::String getWindowName();
    bool isOpen();
    bool pollEvent(sf::Event &event);
//    void setWindow(sf::RenderWindow*);
    void render(std::vector<GameElement> &onDisplay);
    void display();
    void close();

    std::string handleEvents();

    friend class GameElement;

private:
    sf::RenderWindow *renderWindow_;
    float height_;
    float width_;
//    Event event;

};

void Window::createRenderWindow(Window *miniEngine, float width, float height, const std::string &title) {

    miniEngine->renderWindow_ = new sf::RenderWindow(sf::VideoMode(width, height), title);
    miniEngine->setHeight(height);
    miniEngine->setWidth(width);
}

void Window::display() {
    renderWindow_->display();
}

void Window::render(std::vector<GameElement> &onDisplay) {
    renderWindow_->clear();

    sf::Texture roadTexture;
    roadTexture.loadFromFile("/home/margot/Desktop/roadTexture.jpg");
    roadTexture.setRepeated(true);
    sf::Sprite roadSprite(roadTexture, sf::IntRect(0,0, width_, height_));
    renderWindow_->draw(roadSprite);

    sf::Texture carTexture;
    carTexture.loadFromFile("/home/margot/Desktop/car.jpg");
    sf::Sprite carSprite(carTexture, sf::IntRect(0,0, onDisplay[1].getHeightElem(), onDisplay[1].getWidhtElem()));
    carSprite.setPosition(onDisplay[1].getX(), onDisplay[1].getY());
    renderWindow_->draw(carSprite);

//    for (auto it = std::begin(onDisplay); it != std::end(onDisplay); ++it) {    //place for obstruction.
//        GameElement current = (*it);
//        if (current.getId() == 1) {
//            sf::RectangleShape shape(sf::Vector2f(current.getHeightElem(), current.getWidhtElem()));
//            shape.setFillColor(sf::Color::Green);
//            shape.setPosition(current.getX(), current.getY());
//            renderWindow_->draw(shape);
//        }
//    }
}

bool Window::isOpen() {
    return renderWindow_->isOpen();
}


std::string Window::handleEvents() {
    sf::Event event;
    if (renderWindow_->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            return "close";
        }
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Right)
                return "right";
            if (event.key.code == sf::Keyboard::Left)
                return "left";
            if (event.key.code == sf::Keyboard::Up)
                return "up";
            if (event.key.code == sf::Keyboard::Down)
                return "down";
        }
    }
    return "";
}


void Window::close() {
    renderWindow_->close();
}

void Window::setWidth(float width) {
    width_ = width;
}

void Window::setHeight(float height) {
    height_ = height;
}

float Window::getWidth() {
    return width_;
}

float Window::getHeight() {
    return height_;
}


//
//class Event{
//public:
//    Event();
//    ~Event();
//    sf:: Event getEvent();
//    friend class Window;
//
//    sf::Event::EventType  type;
//private:
//    sf::Event event_;
//};
//
//Event::Event() {
//    event_ = sf::Event();
////    type = event_.type;
//
//}
//
//
//
//
//
//sf::Event Event::getEvent() {
//    return event_;
//}


#endif //NFS_NEXT_GEN_UTILS_H
