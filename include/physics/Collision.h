#ifndef PHYSICS_COLLISION_H
#define PHYSICS_COLLISION_H

#include "IElements.h"
#include <vector>

class Collision{
public:
	Collision();
	void setAction(int _action);
private:
	void handleAllChunk();
	int* selectObject();
	vector<IGameElement> obstructionModels;
	int action;
};

#endif //PHYSICS_COLLISION_H
