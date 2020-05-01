//
// Created by margot on 01.05.2020.
//

#ifndef NFS_NEXT_GEN_TESTGAMEELEMENT_H
#define NFS_NEXT_GEN_TESTGAMEELEMENT_H

#include "graphic.h"

class GameElement{
public:
    explicit GameElement(int id, float newWidth, float newHeight, float newPosX, float newPosY);
    ~GameElement();
    void setX(int offsetX, float width);
    void setY(int offsetY, float height);
    float getX();
    float getY();
    float getWidhtElem();
    float getHeightElem();
    void setTexture();
    int getId();
    void move();

private:
    int id;
    float x;
    float y;
    float widthElement;
    float heightElement;
};

GameElement::GameElement(int newId, float newWidth, float newHeight, float newPosX, float newPosY) {
    x = newPosX;
    y = newPosY;
    widthElement = newWidth;
    heightElement = newHeight;
    id = newId;
}

GameElement::~GameElement() {

}

int GameElement::getId() {
    return id;
}

void GameElement::setX(int offsetX, float width) {
    x +=offsetX;
    if (x < 0)
        x = 0;
    if (x + widthElement/2 > width)
        x = width - widthElement/2;
}

void GameElement::setY(int offsetY, float height) {
    y+=offsetY;
    if (y < 0)
        y = 0;
    if (y  > height - 2*heightElement)
        y = height - 2*heightElement;
}

float GameElement::getX() {
    return x;
}

float GameElement::getY() {
    return y;
}

float GameElement::getWidhtElem() {
    return widthElement;
}

float GameElement::getHeightElem() {
    return heightElement;
}


#endif //NFS_NEXT_GEN_TESTGAMEELEMENT_H
