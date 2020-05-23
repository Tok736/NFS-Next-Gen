#ifndef NFS_NEXT_GEN_PHYSICS_H
#define NFS_NEXT_GEN_PHYSICS_H

#include <iostream>
#include <vector>
#include <iostream>
#include <memory>
#include <unordered_map>

using std::pair;
using std::cout;
using std::vector;
using std::shared_ptr;
using std::string;


enum groupsModels {
	group1Height = 112,
	group1Width  = 112,
	group2Height = 112,
	group2Width  = 112,
	group3Height = 112,
	group3Width  = 112,
	group4Height = 112,
	group4Width  = 112,
	group5Height = 112,
	group5Width  = 112,
	group6Height = 112,
	group6Width  = 112,
};

enum groupsCount {
	group1Count  = 5,
	group2Count  = 5,
	group3Count  = 5,
	group4Count  = 5,
	group5Count  = 5,
	group6Count  = 5,
};

enum sizes {
	screenHeight =	900,
	screenWidth =	1440,
	carHeight = 	98,
	carWidth =		47,
	obstrWidth =	112,
	obstrHeight =	112,
	roadHeight =	900,
	RoadWidth =	600,
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

enum carValues{
	maxSpeed = 60,
	maxLeftAngle = -45,
	maxRightAngle = 45,
};
constexpr float aFriction = 0.1f;
constexpr float minSpeed = 1;
constexpr float step = 0.25f;

class IGameElement{
public:
	virtual ~IGameElement() = default;
	virtual int getId() const = 0;
	virtual float getX() const = 0;
	virtual float getY() const = 0;
	virtual float getAngle() const = 0;
};

class MatrixManager{
public:
	void rotatePart(std::vector<float> &matrixA, float angle);//поворот объектной матрицы
	void matrixOverlay(std::vector<float> &matrixA, std::vector<float> &matrixB);//наложение объектных матриц друг на друга, клетки наложения помечаются маркером с определенным весом для расчетов
	void makeBordersCurves(std::vector<float> &matrixA, float coefficient);//деформация объектной матрицы(новые коэффициенты)
};
class Car : public IGameElement{
public:
	Car(): m_id(0), m_v(0), m_angle(0) {};
	Car(int id, float angle, float x, float y) : m_id(id), m_angle(angle), m_v(0){ m_carCentre.first = x; m_carCentre.second = y; }
	float getX() const override { return m_carCentre.first; }
	float getY() const override { return m_carCentre.second; }
	int getId() const override { return m_id; }
	float getAngle() const override { return m_angle; }
	float getV() const { return m_v; }
	void setX(float x) { m_carCentre.first = x; }
	void setY(float y) { m_carCentre.second = y; };
	void setV(float v) { m_v = v; }
	void setAngle(float alpha) { m_angle = alpha; }

private:
	int m_id;
	float m_v;
	float m_angle;
	std::pair<float, float> m_carCentre;
};


class Obstruction: public IGameElement {
public:
	Obstruction() : m_id(0){};
	Obstruction(int id, float x, float y) : m_id(id) { m_obstructionCentre.first = x; m_obstructionCentre.second = y;}
	int getId() const override { return m_id; }
	float getX() const override { return m_obstructionCentre.first; }
	float getY() const override { return m_obstructionCentre.second; }
	float getAngle() const override { return 0; }
	void setId(int id) { m_id = id; }
	void setX(float x) { m_obstructionCentre.first = x; }
	void setY(float y) { m_obstructionCentre.second = y; };
private:
	int m_id;
	std::pair<float, float> m_obstructionCentre;
};

class Collision {
public:
	Collision():m_time(0), wasCollision(false), carBounce(0){ createObjectModels(); }
	void setTime(int time){ m_time = time; }
	void setFps(int fps) {m_fps = fps;}
	void setAction(std::vector<std::shared_ptr<Obstruction>> &elements, std::vector<std::shared_ptr<Car>> &Cars, std::vector<int> &actions);
private:
	MatrixManager Calculator;
	std::unordered_map<int, std::pair<int, int>> objectsSizes; // хранилище размеров всех препятствий, доступ по Id объекта.
	int m_time;
	int m_fps;
	bool wasCollision;
	float carBounce;
private:
	void createObjectModels();
	void recalculateForSingleCar(std::shared_ptr<Car> &car, int &comboAction);
	void getChunk(vector<std::shared_ptr<Obstruction>> &elements, std::shared_ptr<Car> &car);
	void handleAllChunk();
	std::vector<float> selectObject();
};

#endif //NFS_NEXT_GEN_PHYSICS_H
