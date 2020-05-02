//
// Created by margot on 02.05.2020.
//

#ifndef TESTALL_GRAPHIC_H
#define TESTALL_GRAPHIC_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "physics.h"


class Clock{

public:
    Clock() = default;
    ~Clock() = default;
    void restart();
    float getClockMicro();
    float getClockSec();

private:
    sf:: Clock clock_;
};


class Window{
public:
    Window() = default;
    ~Window() = default;

    static void createRenderWindow(Window *miniEngine, float width, float height, const std::string &title);

    float getWidth();
    float getHeight();
    void setWidth(float width);
    void setHeight(float height);
    bool isOpen();
    void render(std::vector<Car> cars, std::vector<Obstruction> roadAndObstcl);
    void display();
    void close();
    void handleEvents(std::vector<int> &actions);

    friend class GameElement;

private:
    sf::RenderWindow *renderWindow_;
    float height_;
    float width_;
//    Event event;

};


#endif //TESTALL_GRAPHIC_H
