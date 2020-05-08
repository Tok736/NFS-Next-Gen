#include "physics.h"
#include <unistd.h>
#include <iostream>
#include "graphic.h"




int main() {

    if (!displayMenu())
        return 0;
//	createIGameElements();

    shared_ptr<Window> window(new Window);
    Window::createRenderWindow(window, screenLength, screenWidth, "Game");



    vector<Obstruction> elements;
    vector<Car> cars;
    vector<int> actions;

    Collision col;
    Car car(0,0,0,0.5 * screenLength,screenWidth - carWidth); //машинка в центре экрана снизу
    Obstruction Road1(0,0, 0);
	Obstruction Road2(0,0, -roadWidth);
	
    cars.push_back(car);
    elements.push_back(Road1);
	elements.push_back(Road2);
    for(int i = 1; i < 5; ++i) {
        Obstruction obstr;
        obstr.setX(i * 40);
        obstr.setY(i * 40);
        obstr.setId(i);
        elements.push_back(obstr);
    }

    Clock clock;
    int action;

    while (window->isOpen())
    {
        float timeInGame = clock.getClockSec() + 10;
        cout << timeInGame <<std::endl;

        window->handleEvents(actions);

        if (!actions.empty() && actions[0] == endOfTheGame)
            window->close();
        else {
            if (!actions.empty())
                action = actions[0];
            else
                action = -1;
            col.setAction(elements, cars, actions, timeInGame);
        }
        window->render(cars, elements, action, timeInGame);
        window->display();
    }

	
	return 0;
}

