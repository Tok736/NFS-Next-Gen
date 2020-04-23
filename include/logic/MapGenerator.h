#ifndef NFS_NEXT_GEN_MAPGENERATOR_H
#define NFS_NEXT_GEN_MAPGENERATOR_H

#include "IElement.h"

class MapGenerator {
    short difficulty;
    std::vector<std::shared_ptr<IGameElement>> mapVector;
public:
    mapGenerator();
    mapGenerator(short difficulty);
    std::vector<std::shared_ptr<IGameElement>> getVector();
};

#endif //NFS_NEXT_GEN_MAPGENERATOR_H
