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

enum collisionType {
	none = 0,
	absBounce = 1, // Абсолютно упругий удар
	noBounce = 2,  // Абсолютно неупругий удар
	glancingBlow = 3, // Скользящий удар
	skid = 4, // занос
};

enum carLifeReduction {
	low = 20,
	medium = 30,
	high = 60,
	all = 100,
};

enum groupsModels {
	group1Height = 68,
	group1Width  = 68,
	group2Height = 112,
	group2Width  = 112,
	group3Height = 95,
	group3Width  = 85,
	group4Height = 85,
	group4Width  = 90,
	group5Height = 112,
	group5Width  = 112,
	group6Height = 112,
	group6Width  = 112,
};

enum groupsType {
	groupSkidStart  = 10,
	groupSkidEnd  = 14,
	groupNoBounceStart = 15,
	groupNoBounceEnd = 17,
	groupBounceStart = 18,
	groupBounceEnd = 18,
};

enum groupsId {
	group1IdStart  = 10,
	group1IdEnd = 10,
	group2IdStart  = 11,
	group2IdEnd = 11,
	group3IdStart  = 12,
	group3IdEnd = 13,
	group4IdStart  = 14,
	group4IdEnd = 14,
	group5IdStart  = 15,
	group5IdEnd = 17,
	group6IdStart  = 18,
	group6IdEnd = 18,
};

enum sizes {
	screenHeight =	900,
	screenWidth =	1440,
	carHeight = 	98,
	carWidth =		47,
	roadHeight =	900,
	roadWidth =	660,
	roadCenter = 720,
	leftRoadBorder = 390,
	rightRoadBorder = 1050,
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
	FpsTime =			50,
	pauseOfTheGame =	100,
	endOfTheGame =		0,
};

enum carValues{
	maxSpeed = 60,
	maxLeftAngle = -45,
	maxRightAngle = 45,
};

enum Severity{
	absoluteDamage = 150,
	highDamage = 100,
	mediumDamage = 60,
	lowDamage = 30,
};
constexpr float aFriction = 0.1f;
constexpr float minSpeed = 1;
constexpr float step = 0.75f;
constexpr int pointsCount = 4;
constexpr int updateTime = 3;
constexpr int transparency = -1;
constexpr int alphaMin = -90;
constexpr int alphaMax = 90;
constexpr int alphaSkid = 35;
constexpr float pi = 3.14159;


class IGameElement{
public:
	virtual ~IGameElement() = default;
	virtual int getId() const = 0;
	virtual float getX() const = 0;
	virtual float getY() const = 0;
	virtual float getAngle() const = 0;
	virtual int getHealthCount() const = 0;
};

class Car : public IGameElement{
public:
	Car(): m_life(all), m_id(0), m_v(0), m_angle(0) {};
	Car(int id, float angle, float x, float y) : m_life(all), m_id(id),  m_v(0), m_angle(angle) { m_carCentre.first = x; m_carCentre.second = y; }
	float getX() const override { return m_carCentre.first; }
	float getY() const override { return m_carCentre.second; }
	int getId() const override { return m_id; }
	float getAngle() const override { return m_angle; }
	int getHealthCount() const override { return m_life; }
	float getV() const { return m_v; }
	void setX(float x) { m_carCentre.first = x; }
	void setY(float y) { m_carCentre.second = y; };
	void setV(float v) { m_v = v; }
	void setAngle(float alpha) { m_angle = alpha; }
	void setLife(int life) { m_life = life; }
private:
	int m_life;
	int m_id;
	float m_v;
	float m_angle;
	std::pair<float, float> m_carCentre;
};


class Obstruction: public IGameElement {
public:
	Obstruction() :  m_life(1), m_id(0) {};
	Obstruction(int id, float x, float y) : m_life(all),  m_id(id) { m_obstructionCentre.first = x; m_obstructionCentre.second = y;}
	int getId() const override { return m_id; }
	int getHealthCount() const override { return m_life; }
	float getX() const override { return m_obstructionCentre.first; }
	float getY() const override { return m_obstructionCentre.second; }
	float getAngle() const override { return 0; }
	void setId(int id) { m_id = id; }
	void setX(float x) { m_obstructionCentre.first = x; }
	void setY(float y) { m_obstructionCentre.second = y; };
private:
	int m_life;
	int m_id;
	std::pair<float, float> m_obstructionCentre;
};

class Collision {
public:
	Collision():m_time(0),  collisionDuration(0), collisionType(none){ createObjectModels(); }
	void setTime(int time){ m_time = time; }
	void setAction(std::vector<std::shared_ptr<Obstruction>> &elements, std::vector<std::shared_ptr<Car>> &Cars, std::vector<int> &actions);
private:
	std::unordered_map<int, std::pair<int, int>> objectsSizes; // хранилище размеров всех препятствий, доступ по Id объекта.
	int m_time;
	int collisionDuration;
	int collisionType;
	float collisionEndAngle;
private:
	void createObjectModels();
	void recalculateForSingleCar(std::shared_ptr<Car> &car, int &comboAction);
	void handleChunk(vector<std::shared_ptr<Obstruction>> &elements, std::shared_ptr<Car> &car);
};

#endif //NFS_NEXT_GEN_PHYSICS_H
