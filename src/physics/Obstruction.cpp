#include "physics/Obstruction.h"

Obstruction::Obstruction(int x, int y, int id, float angle) : x(x), y(y), id(id), angle(angle){

}

Obstruction::~Obstruction() {

}

int Obstruction::getX() {
    return x;
}

int Obstruction::getY() {
    return y;
}

int Obstruction::getId() {
    return id;
}

float Obstruction::getAngle() {
    return angle;
}
