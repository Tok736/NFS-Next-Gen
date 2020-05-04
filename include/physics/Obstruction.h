#ifndef PHYSICS_OBSTRUCTION_H
#define PHYSICS_OBSTRUCTION_H

#include "physics/IElements.h"

class Obstruction : public IGameElement {
    int x;
    int y;
    int id;
    float angle;
public:
    Obstruction(int x = 0, int y = 0, int id = 0, float angle = 0);
    ~Obstruction() override ;
    int getX() override;
    int getY() override;
    int getId() override;
    float getAngle() override;
};

#endif //PHYSICS_OBSTRUCTION_H
