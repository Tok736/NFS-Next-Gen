
#include "../include/physics/physics.h"
#include "../include/graphics//graphic.h"


//road id [0,1]
//cars id [2..9]
//obstraction id [10..20]
//decor id [21..30]

//obstructions id:
// cone - 10
// mud - 11
// oil - 12
// pit - 13
// rock1 - 14
// rock2 - 15
// rock3 - 16
// water - 17
// wheel - 18


//decor id
// tree1 - 21
// tree2 - 22
// tree 3 -23


int main()
{
    shared_ptr<Window> window(new Window);

    if (!displayMenu(window))
        return 0;
//
//    Window::createRenderWindow(window, screenLength, screenWidth, "Game");
//    window->getRenderWindow();

    vector<Obstruction> elements;
    vector<Car> cars;
    vector<int> actions;

    Collision col;
    Car car(2,0,0,0.5 * screenWidth,screenHeight - carHeight); //машинка в центре экрана снизу
    Obstruction Road1(0,0, 0);
    Obstruction Road2(1,0, -roadHeight);
    Obstruction rock(18,0.5 * screenWidth,0);

    cars.push_back(car);
    elements.push_back(Road1);
    elements.push_back(Road2);
    elements.push_back(rock);

    window->createTextures(cars,elements);

    Clock clock;
    int action;

    while (window->isOpen())
    {
        int freq = (int)clock.getClockSec() + 10;
        window->handleEvents(actions);

        if (!actions.empty() && actions[0] == endOfTheGame)
            window->close();
//        else if (!actions.empty() && actions[0] == pauseOfTheGame)
//        {
//            pauseWindow();
//        }
        else {
            if (!actions.empty())
                action = actions[0];
            else
                action = myNoAction;
            col.setFreq(freq);
            col.setAction(elements, cars, actions);
        }
        window->render(cars, elements, action, freq);
        window->display();
    }


    return 0;

}
