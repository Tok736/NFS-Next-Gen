#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <ctime>
#include <cstdlib>
#include "../include/physics/Collision.h"
// Actions
#define ActionsCount 10
#define downKey 0
#define upKey 1
#define leftKey 2
#define rightKey 3
/*
class MockCollision : public Collision { // моки убраны, так как есть простейшая реализация методов
public:
	MOCK_METHOD1(setFreq, void(int freq_));
	MOCK_METHOD3(setAction, void(vector<Obstruction> &RoadElements, vector<Car> &Cars, vector<int> &actions));
};*/

void checkCalculations() {
	Collision col;
	Car car1;
	Obstruction roadUp, roadDown;
	vector<int> actions;
	vector<Obstruction> obstructions;
	vector<Car> cars;
	
	cars.push_back(car1);
	obstructions.push_back(roadUp);
	obstructions.push_back(roadDown);
	srand(time(NULL));
	for (int i = 0; i < ActionsCount; ++i) { // простейшая версия обрабатывает пока только одну команду, работает с одной машинкой и элементом - дорогой.
		actions.push_back(rand() % 3);// В дальнейшем будет возможность обработки нажатия нескольких клавиш и работа с большим количеством препятствий и машинок
		col.setAction(obstructions, cars, actions);
	}
}

TEST(googleTestExample, collisionTest) {

	checkCalculations();
	std::cout << "Collision test\n";
}