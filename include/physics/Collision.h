#ifndef PHYSICS_COLLISION_H
#define PHYSICS_COLLISION_H

#include "IElements.h"
#include "MatrixManager.h"
#include <vector>

class Collision{
public:
	Collision();
	void setAction(std::shared_ptr<IGameElement>> &elements, std::vector<Car> Cars, std::vector<int> actions);
private:
	matrixManager Calculator;
	void handleAllChunk();
	int* selectObject();
	vector<IGameElement> obstructionModels;
	int action;
};

#endif //PHYSICS_COLLISION_H
