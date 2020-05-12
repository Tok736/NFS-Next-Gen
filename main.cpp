#include "physics.h"
#include <unistd.h>
#include <iostream>
#include "graphic.h"
#include "logic/Game.h"




int main()
{
//    shared_ptr<Window> window(new Window);
//
//    if (!displayMenu(window))
//        return 0;
////
////    Window::createRenderWindow(window, screenLength, screenWidth, "Game");
////    window->getRenderWindow();
//
//    vector<Obstruction> elements;
//    vector<Car> cars;
//    vector<int> actions;
//
//    Collision col;
//    Car car(0,0,0,0.5 * screenWidth,screenHeight - carHeight); //машинка в центре экрана снизу
//    Obstruction Road1(0,0, 0);
//    Obstruction Road2(0,0, -roadHeight);
//    Obstruction rock(0,0.5 * screenWidth,0);
//
//    cars.push_back(car);
//    elements.push_back(Road1);
//    elements.push_back(Road2);
//    elements.push_back(rock);
//
//
//    Clock clock;
//    int action;
//
//    while (window->isOpen())
//    {
//        int freq = (int)clock.getClockSec() + 10;
//        window->handleEvents(actions);
//
//        if (!actions.empty() && actions[0] == endOfTheGame)
//            window->close();
//        else {
//            if (!actions.empty())
//                action = actions[0];
//            else
//                action = myNoAction;
//            col.setFreq(freq);
//            col.setAction(elements, cars, actions);
//        }
//        window->render(cars, elements, action, freq);
//        window->display();
//    }

    Game myGame;
    myGame.playGame();
    return 0;
}

