#include "gtest/gtest.h"
#include "../include/logic/MapGenerator.h"

TEST(logicBranchTestExample, MapGeneratorTest) {
    MapGenerator myGen1(10);
    MapGenerator myGen2(7);
    MapGenerator myGen3 (7);

    myGen1.generate();
    myGen2.generate();
    myGen3.generate();

    std::vector<std::shared_ptr<IGameElement>> vec1, vec2, vec3;

    vec1 = myGen1.getVector();
    vec2 = myGen2.getVector();
    vec3 = myGen3.getVector();

    EXPECT_GT(vec1.size(), vec2.size());
    EXPECT_EQ(vec2.size(), vec3.size());
    EXPECT_FALSE(vec2 == vec3);
}
