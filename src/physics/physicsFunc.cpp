#include "physics/physics.h"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <cmath>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>

BOOST_GEOMETRY_REGISTER_BOOST_TUPLE_CS(cs::cartesian)
using namespace boost::geometry;

void addObjectsInMap(std::unordered_map<int, std::pair<int, int>> &objectsSizes, const std::pair<int, int> &id,
					 const std::pair<int, int> &sizes) {
	int idStart = id.first;
	int idEnd = id.second + idStart;
	
	for (; idStart < idEnd; ++idStart)
		objectsSizes.insert(std::make_pair(idStart, std::make_pair(sizes.first, sizes.second)));
}

void Collision::createObjectModels() {
	addObjectsInMap(objectsSizes, std::make_pair(0, group1Count), std::make_pair(group1Height, group1Width));
	addObjectsInMap(objectsSizes, std::make_pair(group1Count, group2Count), std::make_pair(group2Height, group2Width));
	addObjectsInMap(objectsSizes, std::make_pair(group2Count, group3Count), std::make_pair(group3Height, group3Width));
	addObjectsInMap(objectsSizes, std::make_pair(group3Count, group4Count), std::make_pair(group4Height, group4Width));
	addObjectsInMap(objectsSizes, std::make_pair(group4Count, group5Count), std::make_pair(group5Height, group5Width));
}

void CheckUpdateSpeed(int &time, int updateFreq, float &dSbyTic) // проверяет, нужно ли обновлять скорость машинки каждую итерацию главного цикла.
{                                                			  // UpdateFreq устанавливает периодичность изменения
	static int bufTime = time;
	if (time - bufTime >= updateFreq) {
		bufTime = time;
		dSbyTic += step;
	}
	if (time)
		return;
	dSbyTic = minSpeed;
}

void moveRoad(vector<std::shared_ptr<Obstruction>> &elements, float &dSbyTic) {
	if (elements[0]->getY() >= screenHeight)
		elements[0]->setY(elements[1]->getY() - roadHeight + dSbyTic);
	else
		elements[0]->setY(elements[0]->getY() + dSbyTic);
	if (elements[1]->getY() >= screenHeight)
		elements[1]->setY(elements[0]->getY() - roadHeight + dSbyTic);
	else
		elements[1]->setY(elements[1]->getY() + dSbyTic);
	for (int i = 2; i < elements.size(); ++i)
		elements[i]->setY(elements[i]->getY() + dSbyTic);
}

void moveCar(std::shared_ptr<Car> &car, int &comboAction, int time) {
	float x = car->getX();
	static int prevAction = comboAction;
	float y = car->getY();
	float alpha = car->getAngle();
	float dSbyTic = car->getV();
	
	if (comboAction == myNoAction && prevAction == myNoAction) {
		if (alpha > 1 && alpha < 90)
			car->setAngle(alpha - 0.25f * dSbyTic);
		else if (alpha < -1 && alpha > -90)
			car->setAngle(alpha + 0.25f * dSbyTic);
		else
			car->setAngle(0);
	}
	if (alpha != 0)
		car->setX(x + dSbyTic * sin(3.14159f * alpha / 180)); // потом можно заменить на катеты
	if (comboAction == myUp && y - dSbyTic > 0.5 * screenHeight)  //  машинка не может подняться выше середины экрана
		car->setY(y - 5);
	if (comboAction == myDown && y < screenHeight - carHeight) {
		car->setY(y + 5);
	}
	prevAction = comboAction;
	if (comboAction == myLeft && alpha > maxLeftAngle)
		car->setAngle(alpha - 2 * dSbyTic);
	if (comboAction == myRight && alpha < maxRightAngle)
		car->setAngle(alpha + 2 * dSbyTic);
	
}

void Collision::recalculateForSingleCar(std::shared_ptr<Car> &car, int &comboAction) {
	float y = car->getY();
	float dSbyTic = car->getV();
	
	CheckUpdateSpeed(m_time, 3, dSbyTic);
	car->setV(dSbyTic);
	if (!wasCollision) {
		moveCar(car, comboAction, m_time);
	} else {
		car->setY(y + carBounce); //отскок пока ток по вертикали
		carBounce -= aFriction;
	}
}

void Collision::setAction(vector<std::shared_ptr<Obstruction>> &elements, vector<std::shared_ptr<Car>> &Cars, vector<int> &actions) {
	int comboAction = myNoAction;
	
	int i = 0;
	while (i < actions.size() && actions[i] != myNoAction) {
		comboAction = actions[i++];
		/*if (comboAction == myLeftDown)
			cout << "myLeftDown\n";
		if (comboAction == myLeftUp)
			cout << "myLeftDown\n";
		if (comboAction == myRightDown)
			cout << "myRightDown\n";
		if (comboAction == myRightDown)
			cout << "myRightDown\n";*/
		actions.pop_back();
	}
	if (carBounce <= 0)
		getChunk(elements, Cars[0]);
	recalculateForSingleCar(Cars[0], comboAction);
	float dSbyTic = Cars[0]->getV();
	moveRoad(elements, dSbyTic);
}


void Collision::getChunk(vector<std::shared_ptr<Obstruction>> &elements, std::shared_ptr<Car> &car) {
	vector<Obstruction> obstInChunk;
	float dSbyTic = car->getV();
	static int i = 2;
	static int wasChecked = 0;
	float sX = car->getX();
	float sY = car->getY() + 0.5f * carHeight;
	
	if (elements.size() < 2) //кроме дороги вектор не содержит препятствий
		return;
	float obstrY = 0;
	float obstrX = 0;
	while (i < elements.size()) {
		obstrY = elements[i]->getY() + obstrHeight;
		obstrX = elements[i]->getX();
		float obstrXa = obstrX - 0.5f * obstrWidth;
		float obstrXb = obstrX + 0.5f * obstrWidth;
		if (carBounce != 0)
			wasCollision = false;
		if (obstrY < sY)
			break;
		if (wasChecked != i && (sX + 0.5f * carWidth >= obstrXa && sX - 0.5f * carWidth <= obstrXb)) {
			cout << "obstrc" << i << '\n';
			cout << " catch it !!!!!!!\n";
			car->setV(0);
			carBounce = dSbyTic;
			wasCollision = true;
			wasChecked = i;
			break;
		} else if (wasChecked != i && obstrY - (sY + carHeight) <= 0)
			break;
		++i;
	}
}

void Collision::handleAllChunk() {

}