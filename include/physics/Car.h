#ifndef PHYSICS_CAR_H
#define PHYSICS_CAR_H

#include "IElements.h"

using std::pair;

class Car : public IGameElement{
public:
	Car(): id(0), v(0), centerAngle(0){};
	~Car() override;
	int getX() override;
	int getY() override;
	int getId() override;
	float getAngle() override;
	double getV();
	string getDriver();
	void setCarId(int _id);
	void setX(int _x);
	void setY(int _y);
	void setV(double _v);
	void setAngle(float _alpha);

private:
	int id;
	double v;
	double centerAngle;
	pair<int, int> carCentre;
};

#endif //PHYSICS_CAR_H
