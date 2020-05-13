#ifndef PHYSICS_OBSTRUCTION_H
#define PHYSICS_OBSTRUCTION_H

#include "IElements.h"

using std::pair;

class Obstruction: public IGameElement {
public:
	Obstruction() : id(0){};
	Obstruction(int id_, int x_, int y_) : id(id_) { obstructionCentre.first = x_; obstructionCentre.second = y_;}
	int getId() override { return id; }
	int getX() override { return obstructionCentre.first; }
	int getY() override { return obstructionCentre.second; }
	int getAngle() override { return 0; }
	void setId(int _id) { id = _id; }
	void setX(int _x) { obstructionCentre.first = _x; }
	void setY(int _y) { obstructionCentre.second = _y; };
private:
	int id;
	pair<int, int> obstructionCentre;
};

#endif //PHYSICS_OBSTRUCTION_H
