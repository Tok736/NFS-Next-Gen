#ifndef NFS_NEXT_GEN_MAPGENERATOR_H
#define NFS_NEXT_GEN_MAPGENERATOR_H

#include "physics/IElements.h"
#include "physics/Obstruction.h"

#include <vector>
#include <memory>

#define width 580
#define height 600

class MapGenerator {
    short difficulty;
    std::vector<std::shared_ptr<IGameElement>> mapVector;
public:
    MapGenerator(short difficulty = 5);
    ~MapGenerator();
    void generate();
    std::vector<std::shared_ptr<IGameElement>> getVector();
};

#endif //NFS_NEXT_GEN_MAPGENERATOR_H
