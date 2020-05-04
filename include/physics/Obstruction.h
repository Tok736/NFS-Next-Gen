#ifndef PHYSICS_OBSTRUCTION_H
#define PHYSICS_OBSTRUCTION_H

#include "IElements.h"

using std::pair;

class Obstruction: public IGameElement {
public:
	Obstruction() : id(0), x(0), y(0){};
	int getId() override;
	int getX() override;
	int getY() override;
private:
	int id;
	pair<int, int> obstructionCentre;
	int x;
	int y;
};

#endif //PHYSICS_OBSTRUCTION_H
