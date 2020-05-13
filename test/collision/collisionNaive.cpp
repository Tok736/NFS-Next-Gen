#include "../include/physics/Collision.h"
#define screenLength 800
#define screenWidth 600

#define carWidth 55 //размеры текстур должны быть в начале игры закнуты в словарь вида map<id, pair<pathToFile, pair<int width, int length>>
#define carLength 30
#define obstrWidth 60
#define obstrLength 80
#define roadWidth 800
#define RoadLength 600
// ms
#define FpsTime 100
// actions
#define myLeft 4
#define myRight 6
#define myUp 8
#define myDown 2
#define endOfTheGame 0

void Collision::setAction(vector<Obstruction> &elements, vector<Car> &Cars, vector<int> &actions) {

	int speed = Cars[0].getV();
	int x = Cars[0].getX();
	int y = Cars[0].getY();
	
	if (speed <= 0)
		Cars[0].setV(5);
	else if (!actions.empty()) {
		int step = speed + 1;
		if (actions[0] == myUp && y - step > 0.5 * screenWidth && speed < 50) { //  машинка не может подняться выше середины экрана
			Cars[0].setV(step);
			Cars[0].setY(y - step);
		}
		if (actions[0] == myDown && y < screenWidth - carWidth) {
			Cars[0].setY(y + step);
			step -= 0.25 * step;
			Cars[0].setV(step);
		}
		if (actions[0] == myLeft && x - step > 0)
			Cars[0].setX(x - step);
		if (actions[0] == myRight && x + step < screenLength)
			Cars[0].setX(x + step);
		actions.pop_back();
	}
	if (elements[0].getY() >= screenWidth)
		elements[0].setY(elements[1].getY() - roadWidth + speed);
	else
		elements[0].setY(elements[0].getY() + speed); // сдвинули дорогу примерно на 1 см вниз
	if (elements[1].getY() >= screenWidth)
		elements[1].setY(elements[0].getY() - roadWidth + speed);
	else
		elements[1].setY(elements[1].getY() + speed); // сдвинули дорогу примерно на 1 см вниз
}

