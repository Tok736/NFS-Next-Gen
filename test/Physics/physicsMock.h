#ifndef NFS_NEXT_GEN_PHYSICSMOCK_H
#define NFS_NEXT_GEN_PHYSICSMOCK_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "physics/physics.h"

class MockCollision : public Collision {
public:
    MOCK_METHOD0(calculate, void());
};

class MockCar : public Car {
    MOCK_METHOD0(getX, int());
    MOCK_METHOD0(getY, int());
    MOCK_METHOD0(getId, int());
    MOCK_METHOD0(getAngle, float());
};

#endif //NFS_NEXT_GEN_PHYSICSMOCK_H
