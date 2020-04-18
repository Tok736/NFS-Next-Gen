#ifndef PHYSICS_IELEMENTS_H
#define PHYSICS_IELEMENTS_H

class IGameElement{
public:
	virtual int getId() = 0;
	virtual int getX() = 0;
	virtual int getY() = 0;
	virtual float getAngle() = 0;
};

#endif //PHYSICS_IELEMENTS_H
