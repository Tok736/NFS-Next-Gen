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
    int getClockSec();

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
    void render(std::vector<shared_ptr<IGameElement>> &roadAndObstcl, int &actions,  int &timeInGame, bool &isStrike);
    void display();
    void close();
    void handleEvents(std::vector<int> &actions);
    void clear();
    bool pollEvent(sf::Event &event);

    void createTextures();

    shared_ptr<sf::RenderWindow>  getRenderWindow();


private:
    shared_ptr<sf::RenderWindow> renderWindow_;
    unsigned int height_;
    unsigned int width_;
    shared_ptr<sf::Music> music;

    std::map<int, std::vector<sf::Texture>> mapOfRextures;

};



short int displayMenu(const shared_ptr<sf::RenderWindow>& window,const string& name, const std::tuple<vector<string>, vector<int>, vector<int>> &scoreTable);
short int pauseWindow(const shared_ptr<sf::RenderWindow>& window,const int &timeInGame);
pair<pair<string,string>,string>  displayLoginMenu(const shared_ptr<sf::RenderWindow>& window, string &type, const string &errorMassage);
short int displayScoreTable(const shared_ptr<sf::RenderWindow>& window, const std::tuple<vector<string>, vector<int>, vector<int>> &highTable);
short int displayGameOver(const shared_ptr<sf::RenderWindow>& window,const int &timeInGame);

bool countDown(const shared_ptr<sf::RenderWindow>& window);


void setSizeForButton(int menuNum, sf::Text &first,
                      sf::Text &second, sf::Text &third, int size);

bool isContain(const shared_ptr<sf::RenderWindow>& window, const sf::Text& temp);

void renderPause(const shared_ptr<sf::RenderWindow> &window, const sf::Sprite &menuBg,
                 const sf::Text &first, const sf::Text &second, const sf::Text &exitFromGame);



template <typename T>
std::string toString(T val)
{
    std::ostringstream oss;
    oss<<val;
    return oss.str();
}


enum leftTop
{
        leftAngle = 0,
};


#endif //NFS_NEXT_GEN_UTILS_H
