#include "logic/MapGenerator.h"
#include <iostream>

MapGenerator::MapGenerator(short difficulty) : difficulty(difficulty) {
    generate();

//    for (int i = 0; i < mapVector.size(); ++i) {
//        std::cout << "x: " << mapVector[i].getX() << " y: " << mapVector[i].getY() << std::endl;
//    }
}

MapGenerator::~MapGenerator() {}

void MapGenerator::generate() {
    std::srand(time(NULL));
    for (int i = columnWidth / 2; i <= koef * difficulty; i += columnWidth + 200) {
//        mapVector.push_back(std::make_shared<Obstruction>(10 + (rand() % 9), 378 + columnWidth / 2 + columnWidth * (rand() % columnAmount), -i));
        mapVector.push_back(std::make_shared<Obstruction>(16, 378 + columnWidth / 2 + columnWidth * (rand() % columnAmount), -i));

    }

}

vsp_t<Obstruction> MapGenerator::getVector() {
    return mapVector;
}