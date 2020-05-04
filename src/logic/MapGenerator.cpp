#include "logic/MapGenerator.h"

MapGenerator::MapGenerator(short difficulty) : difficulty(difficulty) {}

MapGenerator::~MapGenerator() {}

void MapGenerator::generate() {
    int koef = 1000;
    int columnAmount = 5;
    int columnWidth = width / columnAmount;
    for (int i = columnWidth / 2; i <= koef * difficulty; i += columnWidth) {
        mapVector.push_back(std::make_shared<Obstruction>(Obstruction(1, columnWidth / 2 + columnWidth * (rand() % columnAmount), i)));
    }
}

std::vector<std::shared_ptr<IGameElement>> MapGenerator::getVector() {
    return mapVector;
}