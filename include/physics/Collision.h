#ifndef PHYSICS_COLLISION_H
#define PHYSICS_COLLISION_H

#include "IElements.h"
#include "MatrixManager.h"
#include "Car.h"
#include <vector>

using std::vector;
using std::shared_ptr;

class Collision{
public:
	Collision();
	void setFreq(int _freq);//часота кадров нужна для определения границ области расчетов
	void setAction(vector<shared_ptr<IGameElement>> elements, vector<Car> Cars, vector<int> actions);
private:
	int freq;
	MatrixManager Calculator;
	void handleAllChunk();
	int* selectObject();
	vector<IGameElement> obstructionModels;
	int action;
};

#endif //PHYSICS_COLLISION_H
