#include "physics.h"

void Collision::setAction(vector<Obstruction> &elements, vector<Car> &Cars, vector<int> &actions) {
	int distance = 0;
	int speed = Cars[0].getV();
	int x = Cars[0].getX();
	int y = Cars[0].getY();
	
	if (speed <= 0) {
		Cars[0].setV(50); // 100 px/s
	}
	else if (!actions.empty()){
		int step = 1;
		if (actions[0] == myUp && y - step > 0.5 * screenWidth) { //  машинка не может подняться выше середины экрана
			Cars[0].setV(speed + step);
			Cars[0].setY(y - step);
		}
		if (actions[0] == myDown && y + step < screenWidth)
		{
			Cars[0].setV(speed - step);
			Cars[0].setY(y + step);
		}
		if (actions[0] == myLeft && x - step > 0)
			Cars[0].setX(x - step);
		if (actions[0] == myRight && x + step < screenLength)
			Cars[0].setX(x + step);
		actions.pop_back();
	}
	elements[0].setY(elements[0].getY() + speed); // сдвинули дорогу примерно на 1 см вниз
//	cout << "coordinates of Road and Car on Road:\n";
//	cout << elements[0].getX() << ' ' << elements[0].getY() << '\n';
//	cout << Cars[0].getX() << ' ' << Cars[0].getY() << '\n';
}

