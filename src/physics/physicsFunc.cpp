#include "physics/physics.h"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <cmath>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/foreach.hpp>

namespace bg = boost::geometry;
namespace trans = boost::geometry::strategy::transform;
typedef bg::model::d2::point_xy<float> point_xy;
typedef bg::model::polygon<point_xy> modelArea; // полигон из точек

void addObjectsInMap(std::unordered_map<int, std::pair<int, int>> &objectsSizes, const std::pair<int, int> &id,
					 const std::pair<int, int> &sizes) {
	int idStart = id.first;
	int idEnd = id.second + 1;
	
	for (; idStart < idEnd; ++idStart)
		objectsSizes.insert(std::make_pair(idStart, std::make_pair(sizes.first, sizes.second)));
}

void Collision::createObjectModels() {
	addObjectsInMap(objectsSizes, std::make_pair(group1IdStart, group1IdEnd), std::make_pair(group1Height, group1Width));
	addObjectsInMap(objectsSizes, std::make_pair(group2IdStart, group2IdEnd), std::make_pair(group2Height, group2Width));
	addObjectsInMap(objectsSizes, std::make_pair(group3IdStart, group3IdEnd), std::make_pair(group3Height, group3Width));
	addObjectsInMap(objectsSizes, std::make_pair(group4IdStart, group4IdEnd), std::make_pair(group4Height, group4Width));
	addObjectsInMap(objectsSizes, std::make_pair(group5IdStart, group5IdEnd), std::make_pair(group5Height, group5Width));
	addObjectsInMap(objectsSizes, std::make_pair(group6IdStart, group6IdEnd), std::make_pair(group6Height, group6Width));
}

void CheckUpdateSpeed(int &time, int updateFreq,
					  float &dSbyTic) // проверяет, нужно ли обновлять скорость машинки каждую итерацию главного цикла.
{                                                              // UpdateFreq устанавливает периодичность изменения
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

void moveCar(std::shared_ptr<Car> &car, int &comboAction) {
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
		car->setX(x + dSbyTic * sin(3.14159f * alpha / 180));
	if (comboAction == myUp && y - dSbyTic > 0.5 * screenHeight)  //  машинка не может подняться выше середины экрана
		car->setY(y - dSbyTic * cos(3.14159f * alpha / 180));
	if (comboAction == myDown && y < screenHeight - carHeight) {
		car->setY(y + dSbyTic * cos(3.14159f * alpha / 180));
	}
	prevAction = comboAction;
	if (comboAction == myLeft && alpha > maxLeftAngle)
		car->setAngle(alpha - 2 * dSbyTic);
	if (comboAction == myRight && alpha < maxRightAngle)
		car->setAngle(alpha + 2 * dSbyTic);
	
}

void absolutelyBounce(std::shared_ptr<Car> &car, float &dSbyTic, float &alpha, float &x, float &y, int &collisionDuration) { //Абсолютно упругий удар (для всяких покрышек)
	dSbyTic += aFriction;
	if (dSbyTic < 0) {
		if (alpha != 0)
			car->setX(x + dSbyTic * sin(3.14159f * alpha / 180));
		car->setV(dSbyTic);
		if (y < screenHeight - 0.5 * carHeight)
			car->setY(y - dSbyTic);
		collisionDuration -= 1;
		return;
	}
	collisionDuration = 0;
	car->setV(minSpeed);
}

void rotateByAngle(std::shared_ptr<Car> &car, float &dSbyTic, float &startAngle, float &endAngle, int &collisionDuration) {
	if (startAngle < endAngle)
		car->setAngle(startAngle + dSbyTic);
	else if (startAngle > endAngle)
		car->setAngle(startAngle - dSbyTic);
	collisionDuration -= 1;
}

void Collision::recalculateForSingleCar(std::shared_ptr<Car> &car, int &comboAction) {
	float dSbyTic = car->getV();
	float y = car->getY();
	float x = car->getX();
	float alpha = car->getAngle();
	
	if (!wasCollision) {
		CheckUpdateSpeed(m_time, 3, dSbyTic);
		car->setV(dSbyTic);
		moveCar(car, comboAction);
	} else {
		if (collisionType == absBounce)
			absolutelyBounce(car, dSbyTic, alpha, x, y, collisionDuration);
		else if (collisionType == glancingBlow)
		{
			rotateByAngle(car, dSbyTic, alpha, collisionEndAngle ,collisionDuration);
		}
	}
}

void Collision::setAction(vector<std::shared_ptr<Obstruction>> &elements, vector<std::shared_ptr<Car>> &Cars,
						  vector<int> &actions) {
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
	if (collisionDuration <= 0)
		getChunk(elements, Cars[0]);
	recalculateForSingleCar(Cars[0], comboAction);
	float dSbyTic = Cars[0]->getV();
	if (dSbyTic > 0)
		moveRoad(elements, dSbyTic);
}

void updateArea(modelArea &area, vector<point_xy> &points) {
	area.clear();
	bg::assign_points(area, points);
	points.clear();
}

/*
void rotate(vector<point_xy> &points)
{
	point_xy temp(1.0,1.0);
	point_xy temp2;
	auto it = points.begin();
	trans::rotate_transformer<bg::degree, float, 2, 2> rotate(-90.0);
	for(; it != points.end(); ++it) {
		temp = *it;
		bg::transform(temp, temp2, rotate);
	}
}*/

void changeLife(std::shared_ptr<Car> &car, float &severity, int collisionType) {
	int life = car->getLifeCount();
	switch (collisionType) {
		case (absBounce || noBounce):
		{
			if (severity > 150) // конец игры
				car->setLife(life - all);
			else if (severity > 100)
				car->setLife(life - high);
			else if (severity > 60)
				car->setLife(life - medium);
			else if (severity > 30)
				car->setLife(life - low);
		}
		case glancingBlow:
			car->setLife(life - low);
	}
}

void Collision::getChunk(vector<std::shared_ptr<Obstruction>> &elements, std::shared_ptr<Car> &car) {
	float dSbyTic = car->getV();
	static vector<point_xy> points(4);
	static modelArea carArea;
	static modelArea obstructionArea;
	static int i = 2;
	static int wasChecked = 0;
	float sX = car->getX();
	float sY = car->getY() - 0.5f * carHeight;
	
	points.assign({{sX - 0.5f * carWidth, sY},{sX - 0.5f * carWidth, sY + carHeight},
				   {sX + 0.5f * carWidth, sY + carHeight}, {sX + 0.5f * carWidth, sY}, {sX - 0.5f * carWidth, sY}});
	updateArea(carArea, points);
	static float carModelAreaS = bg::area(carArea);
	
	if (elements.size() < 2) //кроме дороги вектор не содержит препятствий
		return;
	float obstrY = 0;
	float obstrX = 0;
	while (i < elements.size()) {
		obstrY = elements[i]->getY();
		if (obstrY < sY)
			break;
		obstrX = elements[i]->getX();
		float obstrWidth = objectsSizes.find(elements[i]->getId())->second.second;
		float obstrHeight = objectsSizes.find(elements[i]->getId())->second.first;
		points.assign({{obstrX - 0.5f * obstrWidth, obstrY -  0.5f * obstrHeight}, {obstrX - 0.5f * obstrWidth, obstrY}, {obstrX + 0.5f * obstrWidth, obstrY},
					   {obstrX + 0.5f * obstrWidth, obstrY -  0.5f * obstrHeight}, {obstrX - 0.5f * obstrWidth, obstrY -  0.5f * obstrHeight}});
		updateArea(obstructionArea, points);
		wasCollision = false;
		if (wasChecked != i && bg::intersects(carArea, obstructionArea)) {
			
			
			if (std::abs(obstrX - sX) >= 0.9 * carWidth) // условие скользящего удара
			{
				int alpha = (int)(dSbyTic * (std::abs(obstrX - sX) - carWidth)) % 30;
				if (obstrX - sX > 0) {
					car->setAngle(alpha);
					car->setX(sX - 0.5f * carWidth);
				}
				else {
					car->setAngle(-alpha);
					car->setX(sX + 0.5f * carWidth);
				}
				dSbyTic = 0.7f * dSbyTic;
				car->setV(dSbyTic);
				collisionDuration = std::abs(2 * car->getAngle() / dSbyTic);
				collisionEndAngle = -0.75f * car->getAngle();
				collisionType = glancingBlow;
			}
			else {
				std::deque<modelArea> output;
				bg::intersection(carArea, obstructionArea,
								 output); // в зависимости от величины площади модели наложения делаем вывод о тяжести столкновения
				if (carModelAreaS > 0) {
					float collisionArea = 1;
					BOOST_FOREACH(modelArea const &p, output) collisionArea = bg::area(p);
					float severity = 1000 * collisionArea / carModelAreaS + dSbyTic * dSbyTic;
					changeLife(car, severity, absBounce);
					collisionType = absBounce;
				} else
					carModelAreaS = bg::area(carArea);
				//if (car->getLifeCount() <= 0)
				//		assert(false);
				car->setV(-dSbyTic);
				collisionDuration = (int) (dSbyTic / aFriction);
			}
			wasCollision = true;
			wasChecked = i;
			break;
		}
		++i;
	}
}


void Collision::handleAllChunk() {

}