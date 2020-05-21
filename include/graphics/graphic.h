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

    void setWidth(unsigned int width);
    void setHeight(unsigned int height);
    bool isOpen();
    void render(std::vector<shared_ptr<IGameElement>> &roadAndObstcl, int &actions,  int &timeInGame);
    void display();
    void close();
    void handleEvents(std::vector<int> &actions);
    void clear();
    bool pollEvent(sf::Event &event);

    void createTextures(std::vector<shared_ptr<IGameElement>> &roadAndObstcl);

    shared_ptr<sf::RenderWindow>  getRenderWindow();


private:
    shared_ptr<sf::RenderWindow> renderWindow_;
    unsigned int height_;
    unsigned int width_;

    std::map<int, std::vector<sf::Texture>> mapOfRextures;

};


short int displayMenu(const shared_ptr<sf::RenderWindow>& window,const string& name);
short int pauseWindow(const shared_ptr<sf::RenderWindow>& window,const int &timeInGame);
pair<pair<string,string>,string> displayLoginMenu(const shared_ptr<sf::RenderWindow>& window, string &type);



short int buttonIsPressed(const shared_ptr<sf::RenderWindow> &window, int menuNum, const sf::Sprite &menuBg,
                          sf::Text &playerName, sf::Text &singleGame, sf::Text &coopGame, sf::Text &exitFromGame);

void setSizeForButton(const shared_ptr<sf::RenderWindow> &window,int menuNum, sf::Text &first,
                      sf::Text &second, sf::Text &third, int size);

bool isContain(const shared_ptr<sf::RenderWindow>& window, const sf::Text& temp);


pair<pair<string,string>,string> displayLoginMenu(const shared_ptr<sf::RenderWindow>& window, string &type);


template <typename T>
std::string toString(T val)
{
    std::ostringstream oss;
    oss<<val;
    return oss.str();
}



#endif //NFS_NEXT_GEN_UTILS_H
