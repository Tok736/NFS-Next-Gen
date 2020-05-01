//#include <SFML/Graphics.hpp>
#include "../include/graphics/graphic.h"
#include "../include/graphics/testGameElement.h"


int main()
{
    Window *window = new Window();
//    height = window->setHeight(500);
//    window->setWidth(500);
    float width = 580;
    float height = 600;
    Window::createRenderWindow(window, width, height,"game");

    GameElement road(0, width, height, 0, 0);
    GameElement car(1, 200, 100,width/2, height);

    std::vector<GameElement> onDisplay;
    onDisplay.push_back(road);
    onDisplay.push_back(car);


    while (window->isOpen())
    {

        std::string action = window->handleEvents();
        if (action == "close")
            window->close();
        else if(action == "right") {
            onDisplay[1].setX(5, width);
        }
        else if (action == "left")
            onDisplay[1].setX(-5, width);
        else if(action == "up") {
            onDisplay[1].setY(-5, height);
        }
        else if (action == "down")
            onDisplay[1].setY(5, height);

        window->render(onDisplay);
        window->display();

    }

    return 0;
}