#ifndef NFS_NEXT_GEN_PHYSICS_H
#define NFS_NEXT_GEN_PHYSICS_H

#include <iostream>
#include <vector>
#include <iostream>
#include <memory>

// px
enum sizes {
	screenHeight =	900,
	screenWidth =	1440,
	carHeight = 	47,
	carLength =		98,
	obstrWidth =	60,
	obstrLength =	80,
	roadHeight =	900,
	RoadLength =	600,
};

enum actions {
	myLeft =		-1,
	myRightDown =	-2,
	myDown =		-3,
	myLeftDown =	-4,
	myNoAction =	0,
	myRight =		1,
	myLeftUp =		2,
	myUp =			3,
	myRightUp =		4,
};
enum gameEvents {
	FpsTime =			100,
	pauseOfTheGame =	100,
	endOfTheGame =		0,
};

class IGameElement{
public:
	virtual ~IGameElement() = default;
	virtual int getId() const = 0;
	virtual int getX() const = 0;
	virtual int getY() const = 0;
	virtual int getAngle() const = 0;
};

class MatrixManager{
public:
	void rotatePart(std::vector<int> &matrixA, int angle);//поворот объектной матрицы
	void matrixOverlay(std::vector<int> &matrixA, std::vector<int> &matrixB);//наложение объектных матриц друг на друга, клетки наложения помечаются маркером с определенным весом для расчетов
	void makeBordersCurves(std::vector<int> &matrixA, float coefficient);//деформация объектной матрицы(новые коэффициенты)
};

class Car : public IGameElement{
public:
	Car(): m_id(0), m_v(0), m_angle(0) {};
	Car(int id, int angle, int x, int y) : m_id(id), m_angle(angle), m_v(0){ m_carCentre.first = x; m_carCentre.second = y; }
	int getX() const override { return m_carCentre.first; }
	int getY() const override { return m_carCentre.second; }
	int getId() const override { return m_id; }
	int getAngle() const override { return m_angle; }
	int getV() const { return m_v; }
	void setX(int x) { m_carCentre.first = x; }
	void setY(int y) { m_carCentre.second = y; };
	void setV(int v) { m_v = v; }
	void setAngle(int alpha) { m_angle = alpha; }

private:
	int m_id;
	int m_v;
	int m_angle;
	std::pair<int, int> m_carCentre;
};

class Obstruction: public IGameElement {
public:
	Obstruction() : m_id(0){};
	Obstruction(int id, int x, int y) : m_id(id) { m_obstructionCentre.first = x; m_obstructionCentre.second = y;}
	int getId() const override { return m_id; }
	int getX() const override { return m_obstructionCentre.first; }
	int getY() const override { return m_obstructionCentre.second; }
	int getAngle() const override { return 0; }
	void setId(int id) { m_id = id; }
	void setX(int x) { m_obstructionCentre.first = x; }
	void setY(int y) { m_obstructionCentre.second = y; };
private:
	int m_id;
	std::pair<int, int> m_obstructionCentre;
};

class Collision{
public:
	Collision():m_freq(0){};
	void setFreq(int freq){ m_freq = freq; }//часота кадров нужна для определения границ области расчетов
	void setAction(std::vector<std::shared_ptr<Obstruction>> &elements, std::vector<std::shared_ptr<Car>> &Cars, std::vector<int> &actions);
private:
	MatrixManager Calculator;
	int m_freq;
private:
	void recalculateForSingleCar(std::shared_ptr<Car> &car, int &comboAction);
	void handleAllChunk();
	std::vector<int> selectObject();
};

#endif //NFS_NEXT_GEN_PHYSICS_H
