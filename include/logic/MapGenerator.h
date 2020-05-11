#ifndef NFS_NEXT_GEN_MAPGENERATOR_H
#define NFS_NEXT_GEN_MAPGENERATOR_H

#include "physics/IElements.h"
#include "physics/Obstruction.h"

#include <vector>
#include <memory>

//#define width 580
//#define height 600

template<typename T> using sp_t = std::shared_ptr<T>;
template<typename T> using vsp_t = std::vector<sp_t<T>>;

class MapGenerator {
    short difficulty;
    vsp_t<IGameElement> mapVector;
public:
    MapGenerator(short difficulty = 1);
    ~MapGenerator();
    void generate();
    vsp_t<IGameElement> getVector();
};

#endif //NFS_NEXT_GEN_MAPGENERATOR_H
