#ifndef PHYSICS_COLLISION_H
#define PHYSICS_COLLISION_H

#include "IElements.h"
#include "MatrixManager.h"
#include "Car.h"
#include "Obstruction.h"
#include <vector>

using std::vector;
using std::shared_ptr;

class Collision{
public:
	Collision();
	void setFreq(int _freq);//часота кадров нужна для определения границ области расчетов
	void setAction(vector<Obstruction> &RoadElements, vector<Car> &Cars, vector<int> &actions);
private:
	int freq;
	MatrixManager Calculator;
	void handleAllChunk();
	void centerMassCalc();
	int* selectObject();
};

#endif //PHYSICS_COLLISION_H
