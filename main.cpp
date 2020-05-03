#include "physics.h"
#include <unistd.h>
#include <iostream>


//  ПОСМОТРИТЕ define в physics.h

void createIGameElements() {
	vector<Obstruction> elements;
	vector<Car> cars;
	vector<int> actions(1, Up);
	
	Collision col;
	Car car(0,0,0,0.5 * screenLength,screenWidth - 0.5 * carWidth); //машинка в центре экрана снизу
	Obstruction Road(0,0.5 * screenLength, 0.5 * screenWidth); // центр текстуры "дорога" в центре экрана.
	
	cars.push_back(car);
	elements.push_back(Road);
	
	for(int i = 1; i < 5; ++i) {
		Obstruction obstr;
		obstr.setX(i * 40);
		obstr.setY(i * 40);
		obstr.setId(i);
		elements.push_back(obstr);
	}
	while (true) {
		if (elements[0].getY() > screenWidth + 0.5 * roadWidth)
			break;
		actions[0] = Up; // Left, Right, Down
		col.setAction(elements, cars, actions);
		sleep(1);
	}
}

int main() {
	createIGameElements();
	
	return 0;
}

