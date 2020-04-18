#ifndef PHYSICS_OBSTRUCTION_H
#define PHYSICS_OBSTRUCTION_H

#include "IElements.h"

using std::pair;

class Obstruction: public IGameElement {
	int id;
	pair<int, int> obstructionCentre;
	int x;
	int y;
public:
	int getId() override;
	int getX() override;
	int getY() override;
};

#endif //PHYSICS_OBSTRUCTION_H
