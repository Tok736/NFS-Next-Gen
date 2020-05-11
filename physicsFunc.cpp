#include "physics.h"

void moveRoadDown(vector<Obstruction> &elements, int &speed) {
	if (elements[0].getY() >= screenHeight)
		elements[0].setY(elements[1].getY() - roadHeight + speed);
	else
		elements[0].setY(elements[0].getY() + speed); // сдвинули дорогу примерно на 1 см вниз
	if (elements[1].getY() >= screenHeight)
		elements[1].setY(elements[0].getY() - roadHeight + speed);
	else
		elements[1].setY(elements[1].getY() + speed); // сдвинули дорогу примерно на 1 см вниз
}

void Collision:: recalculateForSingleCar(Car &car, int &comboAction) {
	int x = car.getX();
	int y = car.getY();
	int speed = freq / 10;
	
	if (speed <= 0)
		car.setV(5);
	else if (comboAction) {
		int step = speed + 1;
		if (comboAction == myUp && y - step > 0.5 * screenHeight && speed < 50) { //  машинка не может подняться выше середины экрана
			car.setV(step);
			car.setY(y - step);
		}
		if (comboAction== myDown && y < screenHeight - carHeight) {
			car.setY(y + step);
			step -= 0.25 * step;
			car.setV(step);
		}
		if (comboAction== myLeft && x - step > 0)
			car.setX(x - step);
		if (comboAction== myRight && x + step < screenHeight)
			car.setX(x + step);
	}
}

void Collision::setAction(vector<Obstruction> &elements, vector<Car> &Cars, vector<int> &actions) {
    int speed = freq / 10;
    int comboAction = myNoAction;
    
    for (auto & Car : Cars) {
		if (!actions.empty()) {
			int i = 0;
			while (i < actions.size() && actions[i] != myNoAction) {
				comboAction += actions[i++];
				if (comboAction == myLeftDown)
					cout << "myLeftDown\n";
				if (comboAction == myLeftUp)
					cout << "myLeftDown\n";
				if (comboAction == myRightDown)
					cout << "myRightDown\n";
				if (comboAction == myRightDown)
					cout << "myRightDown\n";
				actions.pop_back();
			}
			recalculateForSingleCar(Car, comboAction);
		}
	}
  
    moveRoadDown(elements, speed);
}

