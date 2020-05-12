#include "MapGenerator.h"
#include <iostream>

#define width 672  //ширина дороги [378;1050]
#define height 900

MapGenerator::MapGenerator(short difficulty) : difficulty(difficulty) {
    this->generate();

//    for (int i = 0; i < mapVector.size(); ++i) {
//        std::cout << "x: " << mapVector[i]->getX() << " y: " << mapVector[i]->getY() << std::endl;
//    }
}

MapGenerator::~MapGenerator() {}

void MapGenerator::generate() {
    int koef = 1000;
    int columnAmount = 5;
    int columnWidth = width / columnAmount;
    std::srand(time(NULL));
    for (int i = columnWidth / 2; i <= koef * difficulty; i += columnWidth) {
        mapVector.push_back(Obstruction(0, 378 + columnWidth / 2 + columnWidth * (rand() % columnAmount), i));
    }
}

std::vector<Obstruction> MapGenerator::getVector() {
    return mapVector;
}