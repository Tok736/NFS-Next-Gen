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
public:
    MOCK_METHOD0(getX, int());
    MOCK_METHOD0(getY, int());
    MOCK_METHOD0(getId, int());
    MOCK_METHOD0(getAngle, float());
};

class MockAbstractDataBase : public AbstractDataBase {
public:
    MOCK_METHOD2(getAutorizeUser, int(std::string nickname, std::string password));
    MOCK_METHOD1(getUserNickname, std::string(int id));
    MOCK_METHOD0(getExperience, int());
};

#endif //NFS_NEXT_GEN_PHYSICSMOCK_H
