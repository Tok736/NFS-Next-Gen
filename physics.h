#ifndef TESTALL_PHYSICS_H
#define TESTALL_PHYSICS_H
#include "vector"
#include <memory>

using std::pair;
using std::vector;
using std::shared_ptr;
using std::string;

class IGameElement{
public:
	virtual ~IGameElement() = default;
	virtual int getId() = 0;
	virtual int getX() = 0;
	virtual int getY() = 0;
	virtual float getAngle() = 0;
};

class Car : public IGameElement{
public:
	Car(): id(0), v(0), centerAngle(0), idUser(0){};
	int getX() override { return carCentre.first; }
	int getY() override { return carCentre.second; }
	int getId() override { return id; }
	float getAngle() override { return centerAngle; }
	double getV() { return v; }
	int getDriver() { return idUser; }
	void setUserId(int _id) { idUser = _id; }
	void setX(int _x) { carCentre.first = _x; }
	void setY(int _y) { carCentre.second = _y; };
	void setV(double _v) { v = _v; }
	void setAngle(float _alpha) { centerAngle = _alpha; }

private:
	int id;
	int idUser;
	double v;
	float centerAngle;
	pair<int, int> carCentre;
};

class MatrixManager{
public:
	void rotatePart(int *matrixA, float angle);//поворот объектной матрицы
	void matrixOverlay(int *matrixA, int *matrixB);//наложение объектных матриц друг на друга, клетки наложения помечаются маркером с определенным весом для расчетов
	void makeBordersCurves(int *matrixA, float coefficient);//деформация объектной матрицы(новые коэффициенты)
};


class Collision{
public:
	Collision();
	void setFreq(int _freq);//часота кадров нужна для определения границ области расчетов
	void setAction(vector<shared_ptr<IGameElement>> elements, vector<Car> Cars, vector<int> actions);
private:
	int freq;
	MatrixManager Calculator;
	void handleAllChunk();
	int* selectObject();
	vector<Car> Cars;
	vector<shared_ptr<IGameElement>> Chunk;
	vector<int> Actions;
};

class Obstruction: public IGameElement {
public:
	Obstruction() : id(0){};
	int getId() override { return id; }
	int getX() override { return obstructionCentre.first; }
	int getY() override { return obstructionCentre.second; }
	float getAngle() override { return 0; }
	void setId(int _id) { id = _id; }
	void setX(int _x) { obstructionCentre.first = _x; }
	void setY(int _y) { obstructionCentre.second = _y; };
private:
	int id;
	pair<int, int> obstructionCentre;
};

#endif
