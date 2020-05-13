#ifndef PHYSICS_CAR_H
#define PHYSICS_CAR_H

#include "IElements.h"
#include <vector>
#include <string>

using std::pair;
using std::string;

class Car : public IGameElement{
public:
	Car(): id(0), v(0), centerAngle(0), idUser(0){};
	Car(int _id, int _idUser, int _angle, int _x, int _y) : id(_id), idUser(_idUser), centerAngle(_angle), v(0){ carCentre.first = _x; carCentre.second = _y; }
	int getX() override { return carCentre.first; }
	int getY() override { return carCentre.second; }
	int getId() override { return id; }
	int getAngle() override { return centerAngle; }
	int getV() { return v; }
	int getDriver() { return idUser; }
	void setUserId(int _id) { idUser = _id; }
	void setX(int _x) { carCentre.first = _x; }
	void setY(int _y) { carCentre.second = _y; };
	void setV(int _v) { v = _v; }
	void setAngle(int _alpha) { centerAngle = _alpha; }

private:
	int id;
	int idUser;
	int v;
	int centerAngle;
	pair<int, int> carCentre;
};


#endif //PHYSICS_CAR_H
