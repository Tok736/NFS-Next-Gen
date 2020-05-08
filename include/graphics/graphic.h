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

    static void createRenderWindow(shared_ptr<Window> miniEngine, unsigned int width, unsigned int height, const std::string &title);

    float getWidth() const;
    float getHeight() const;
    void setWidth(unsigned int width);
    void setHeight(unsigned int height);
    bool isOpen();
//    void render(const std::vector<Car> &cars, const std::vector<Obstruction>& roadAndObstcl, int actions);
    void render(std::vector<Car> cars, const std::vector<Obstruction> roadAndObstcl, int actions,  float timeInGame);
    void display();
    void close();
    void handleEvents(std::vector<int> &actions);
    void clear();
    void draw(sf::Sprite &toDraw);
    shared_ptr<sf::RenderWindow> getWindow();
    bool pollEvent(sf::Event &event);


    friend class GameElement;

private:
    shared_ptr<sf::RenderWindow> renderWindow_;
    unsigned int height_;
    unsigned int width_;
//    Event event;

};


bool isMenu(std::shared_ptr<Window> &window);
bool displayMenu();


#endif //NFS_NEXT_GEN_UTILS_H
