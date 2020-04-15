#include "gtest/gtest.h"
#include "sum/sum.h"

TEST(googleTestExample, SumTest) {
    int a = 5, b = 7;
    int result = 12;
    EXPECT_EQ(sum(a, b), result);
}