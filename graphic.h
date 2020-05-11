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

    static void createRenderWindow(shared_ptr<Window> miniEngine, float width, float height, const std::string &title);

    unsigned int getWidth() const;
    unsigned int getHeight() const;
    void setWidth(float width);
    void setHeight(float height);
    bool isOpen();
    void render(std::vector<Car> cars, const std::vector<Obstruction> roadAndObstcl, int actions,  float timeInGame);
    void display();
    void close();
    void handleEvents(std::vector<int> &actions);
    void clear();
    void draw(sf::Sprite &toDraw);
    shared_ptr<sf::RenderWindow> getWindow();
    bool pollEvent(sf::Event &event);
    void draw(sf::Text &toDraw);
    shared_ptr<sf::RenderWindow>  getRenderWindow();

    friend class GameElement;

private:
    shared_ptr<sf::RenderWindow> renderWindow_;
    unsigned int height_;
    unsigned int width_;
//    Event event;

};

short int isMenu(std::shared_ptr<Window> &window);
short int displayMenu(std::shared_ptr<Window> &window);

#endif //TESTALL_GRAPHIC_H
