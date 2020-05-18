//
// Created by margot on 15.04.2020.
//

#ifndef NFS_NEXT_GEN_UTILS_H
#define NFS_NEXT_GEN_UTILS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "wrap.h"
#include "../physics/physics.h"
#include <sstream>
#include <unistd.h>

using std::pair;
using std::string;

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

    unsigned int getWidth() const;
    unsigned int getHeight() const;
    void setWidth(unsigned int width);
    void setHeight(unsigned int height);
    bool isOpen();
    void render(std::vector<shared_ptr<IGameElement>> &roadAndObstcl, int &actions,  int &timeInGame);
    void display();
    void close();
    void handleEvents(std::vector<int> &actions);
    void clear();
    void draw(const sf::Sprite& toDraw);
    void draw(const sf::RectangleShape& toDraw);
    void draw(const sf::Text& toDraw);
    shared_ptr<sf::RenderWindow> getWindow();
    bool pollEvent(sf::Event &event);

    void createTextures(std::vector<shared_ptr<IGameElement>> &roadAndObstcl);

    shared_ptr<sf::RenderWindow>  getRenderWindow();


private:
    shared_ptr<sf::RenderWindow> renderWindow_;
    unsigned int height_;
    unsigned int width_;

    std::map<int, std::vector<sf::Texture>> mapOfRextures;

};


short int isMenu(std::shared_ptr<Window> &window,const string& name);
short int displayMenu(std::shared_ptr<Window> &window,const string& name);

short int pauseWindow(std::shared_ptr<Window> &window,const int &timeInGame);
short int isPause(std::shared_ptr<Window> &window,const int &timeInGame);

pair<pair<string,string>,string> displayLoginMenu(string &type);
pair<pair<string,string>,string>  isLogin(string &type);

bool countDown(std::shared_ptr<Window> &window);

template <typename T>
std::string toString(T val)
{
    std::ostringstream oss;
    oss<<val;
    return oss.str();
}


#endif //NFS_NEXT_GEN_UTILS_H
