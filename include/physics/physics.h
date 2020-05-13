#ifndef NFS_NEXT_GEN_PHYSICS_H
#define NFS_NEXT_GEN_PHYSICS_H

#include <iostream>
#include <vector>
#include <iostream>
#include <memory>

using std::pair;
using std::cout;
using std::vector;
using std::shared_ptr;
using std::string;


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

class IGameElement{
public:
	virtual ~IGameElement() = default;
	virtual int getId() = 0;
	virtual int getX() = 0;
	virtual int getY() = 0;
	virtual int getAngle() = 0;
};

class MatrixManager{
public:
	void rotatePart(int *matrixA, float angle);//поворот объектной матрицы
	void matrixOverlay(int *matrixA, int *matrixB);//наложение объектных матриц друг на друга, клетки наложения помечаются маркером с определенным весом для расчетов
	void makeBordersCurves(int *matrixA, float coefficient);//деформация объектной матрицы(новые коэффициенты)
};

class Car : public IGameElement{
public:
	Car(): id(0), v(0), centerAngle(0), idUser(0){};
	Car(int _id, int _idUser, int _angle, int _x, int _y) : id(_id), idUser(_idUser), centerAngle(_angle), v(0){ carCentre.first = _x; carCentre.second = _y; }
	int getX() override { return carCentre.first; }
	int getY() override { return carCentre.second; }
	int getId() override { return id; }
	int getAngle() override { return centerAngle; }
	int getV() { return v; }
	int getDriver() { return idUser; }
	void setUserId(int _id) { idUser = _id; }
	void setX(int _x) { carCentre.first = _x; }
	void setY(int _y) { carCentre.second = _y; };
	void setV(int _v) { v = _v; }
	void setAngle(int _alpha) { centerAngle = _alpha; }

private:
	int id;
	int idUser;
	int v;
	int centerAngle;
	pair<int, int> carCentre;
};


class Obstruction: public IGameElement {
public:
	Obstruction() : id(0){};
	Obstruction(int id_, int x_, int y_) : id(id_) { obstructionCentre.first = x_; obstructionCentre.second = y_;}
	int getId() override { return id; }
	int getX() override { return obstructionCentre.first; }
	int getY() override { return obstructionCentre.second; }
	int getAngle() override { return 0; }
	void setId(int _id) { id = _id; }
	void setX(int _x) { obstructionCentre.first = _x; }
	void setY(int _y) { obstructionCentre.second = _y; };
private:
	int id;
	pair<int, int> obstructionCentre;
};


class Collision{
public:
	Collision():freq(0){};
	void setFreq(int _freq){ freq = _freq; }//часота кадров нужна для определения границ области расчетов
	void setAction(vector<std::shared_ptr<Obstruction>> &elements, vector<std::shared_ptr<Car>> &Cars, vector<int> &actions);
private:
	int freq;
	MatrixManager Calculator;
	void recalculateForSingleCar(std::shared_ptr<Car> &car, int &comboAction);
	void handleAllChunk(){};
	int* selectObject(){ return nullptr; }
};

#endif //NFS_NEXT_GEN_PHYSICS_H
