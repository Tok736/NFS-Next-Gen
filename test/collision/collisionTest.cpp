#include "gtest/gtest.h"
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include "../include/physics/Collision.h"
#include "../include/physics/Obstruction.h"
// Actions
#define ActionsCount 10
#define downKey 0
#define upKey 1
#define leftKey 2
#define rightKey 3

void checkCalculations() {
	Collision col;
	vector<int> actions;
	
	srand(time(NULL));
	for (int i = 0; i < ActionsCount; ++i)
		actions.push_back(rand() % 3);
	for (int i = 0; i < ActionsCount; ++i) {
		int action = actions.back();
		actions.pop_back();
	}
}

TEST(googleTestExample, collisionTest) {

	
	std::cout << "Collision test\n";
}