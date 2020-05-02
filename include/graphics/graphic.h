//
// Created by margot on 15.04.2020.
//

#ifndef NFS_NEXT_GEN_UTILS_H
#define NFS_NEXT_GEN_UTILS_H

#include <SFML/Graphics.hpp>
#include <string>
#include "wrap.h"
#include "../phisics/physics.h"

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
//    sf::RenderWindow *getRenderWindow();
    float getWidth();
    float getHeight();
    void setWidth(float width);
    void setHeight(float height);
    bool isOpen();
//    void setWindow(sf::RenderWindow*);
    void render(std::vector<Car> cars, std::vector<Obstruction> roadElements);
    void display();
    void close();
    void handleEvents(std::vector<int> &actions);

private:
    sf::RenderWindow *renderWindow_;
    float height_;
    float width_;

};



#endif //NFS_NEXT_GEN_UTILS_H
