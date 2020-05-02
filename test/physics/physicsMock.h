//
// Created by margot on 02.05.2020.
//

#ifndef NFS_NEXT_GEN_PHYSICSMOCK_H
#define NFS_NEXT_GEN_PHYSICSMOCK_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "phisics/physics.h"

class MockCar : public Car{
public:
    MOCK_METHOD0(getId, int());
    MOCK_METHOD0(getX, int());
    MOCK_METHOD0(getY, int());
    MOCK_METHOD0(getAngle, int());
};

class MockObstruction : public Obstruction{
    MOCK_METHOD0(getId, int());
    MOCK_METHOD0(getX, int());
    MOCK_METHOD0(getY, int());
    MOCK_METHOD0(getAngle, int());
};

#endif //NFS_NEXT_GEN_PHYSICSMOCK_H
