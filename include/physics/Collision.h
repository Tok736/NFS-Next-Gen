#ifndef PHYSICS_COLLISION_H
#define PHYSICS_COLLISION_H

#include "IElements.h"
#include "MatrixManager.h"
#include "Car.h"
#include "Obstruction.h"
#include <vector>

// px
#define screenHeight 900
#define screenWidth 1440

#define carHeight 55 //размеры текстур должны быть в начале игры закнуты в словарь вида map<id, pair<pathToFile, pair<int width, int length>>
#define carLength 30
#define obstrWidth 60
#define obstrLength 80
#define roadHeight 900
#define RoadLength 600
// ms
#define FpsTime 100
// actions



#define myLeft		-1
#define myRightDown -2
#define myDown		-3
#define myLeftDown	-4
#define myNoAction	 0
#define myRight		 1
#define myLeftUp	 2
#define myUp		 3
#define myRightUp	 4

#define pauseOfTheGame 100
#define endOfTheGame 0

using std::vector;

class Collision{
public:
	Collision():freq(0){};
	void setFreq(int _freq){ freq = _freq; }//часота кадров нужна для определения границ области расчетов
	void setAction(vector<Obstruction> &elements, vector<Car> &Cars, vector<int> &actions);
private:
	int freq;
	MatrixManager Calculator;
	void recalculateForSingleCar(Car &car, int &comboAction);
	void handleAllChunk(){};
	int* selectObject(){ return nullptr; }
};


#endif //PHYSICS_COLLISION_H
