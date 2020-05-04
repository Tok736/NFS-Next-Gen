#ifndef PHYSICS_COLLISION_H
#define PHYSICS_COLLISION_H

#include "IElements.h"
#include "MatrixManager.h"
#include "Car.h"
#include "Obstruction.h"
#include <vector>

using std::vector;

class Collision{
public:
	Collision():freq(0){};
	void setFreq(int _freq) { freq = _freq; }//часота кадров нужна для определения границ области расчетов
	void setAction(vector<Obstruction> &elements, vector<Car> &Cars, vector<int> &actions);
private:
	int freq;
	MatrixManager Calculator;
	void handleAllChunk(){};
	void centerMassCalculation(){};
	int* selectObject(){ return nullptr; }
};

#endif //PHYSICS_COLLISION_H
