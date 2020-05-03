#include "physics.h"
#include <unistd.h>
#include <iostream>
#include "graphic.h"


int main() {
//	createIGameElements();
    auto *window = new Window;
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

    sf::Clock clock;

    while (window->isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();

        clock.restart();
        time = time/800;

        window->handleEvents(actions);
        if (!actions.empty() && actions[0] == endOfTheGame)
            window->close();
        else
            col.setAction(elements, cars, actions);
        window->render(cars, elements);
        window->display();
    }


	
	return 0;
}

