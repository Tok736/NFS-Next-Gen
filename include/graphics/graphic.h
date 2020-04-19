//
// Created by margot on 15.04.2020.
//

#ifndef NFS_NEXT_GEN_UTILS_H
#define NFS_NEXT_GEN_UTILS_H

#include <SFML/Graphics.hpp>
#include <string>

class Window{
public:
    Window();
    ~Window();
    sf::RenderWindow *getRenderWindow();
    unsigned int getWidth();
    unsigned int getHeight();
    sf::String getWindowName();
    void setWindow(sf::RenderWindow*);
    void render(sf::RenderWindow*, elements);
    void dysplay();
    void close();

private:
    sf::RenderWindow *window_;
    unsigned int height_;
    unsigned int width_;
    std::string window_name_;

};


class Event{
public:
    sf:: Event getEvent();

private:
    sf::Event event;
};

#endif //NFS_NEXT_GEN_UTILS_H
