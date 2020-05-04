#ifndef NFS_NEXT_GEN_PHYSICS_H
#define NFS_NEXT_GEN_PHYSICS_H

#include "physics/IElements.h"

class Car : public IGameElement {  //методы этого класса я не испоьзую
public:
    virtual int getX() = 0;
    virtual int getY() = 0;
    virtual int getId() = 0;
    virtual float getAngle() = 0;
};

class Collision {
public:
    virtual void calculate() = 0;
};

#endif //NFS_NEXT_GEN_PHYSICS_H
