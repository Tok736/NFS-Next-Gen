#include "physics/physics.h"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>

using namespace boost::geometry;


void moveRoadDown(vector<std::shared_ptr<Obstruction>> &elements, int &speed) {
	if (elements[0]->getY() >= screenHeight)
		elements[0]->setY(elements[1]->getY() - roadHeight + speed);
	else
		elements[0]->setY(elements[0]->getY() + speed);
	if (elements[1]->getY() >= screenHeight)
		elements[1]->setY(elements[0]->getY() - roadHeight + speed);
	else
		elements[1]->setY(elements[1]->getY() + speed);
	for (int i = 2; i < elements.size(); ++i)
		elements[i]->setY(elements[i]->getY() + speed);
}

void Collision:: recalculateForSingleCar(std::shared_ptr<Car> &car, int &comboAction) {
	int x = car->getX();
	int y = car->getY();
	int speed = freq / 10;
	
	model::d2::point_xy<int> p1(1, 1), p2(2, 2);
//	std::cout << "Distance p1-p2 is: " << distance(p1, p2) << std::endl;
	/*QRect r1(100, 200, 15, 15);
	QRect r2(110, 210, 20, 20);
	if (overlaps(r1, r2))
	{
		assign_values(r2, 200, 300, 220, 320);
	}*/
	/*#include <boost/geometry/geometries/adapted/boost_tuple.hpp>
	
	BOOST_GEOMETRY_REGISTER_BOOST_TUPLE_CS(cs::cartesian)
	double points[][2] = {{2.0, 1.3}, {4.1, 3.0}, {5.3, 2.6}, {2.9, 0.7}, {2.0, 1.3}};
	model::polygon<model::d2::point_xy<double> > poly;
	append(poly, points);
	boost::tuple<double, double> p = boost::make_tuple(3.7, 2.0);
	std::cout << "Point p is in polygon? " << std::boolalpha << within(p, poly) << std::endl;*/
	
	
	
	if (speed <= 0)
		car->setV(5);
	else if (comboAction) {
		int step = speed + 1;
		if (comboAction == myUp && y - step > 0.5 * screenHeight && speed < 50) { //  машинка не может подняться выше середины экрана
			car->setV(step);
			car->setY(y - step);
		}
		if (comboAction== myDown && y < screenHeight - carHeight) {
			car->setY(y + step);
			step -= 0.25 * step;
			car->setV(step);
		}
		if (comboAction== myLeft && x - step > 0)
			car->setX(x - step);
		if (comboAction== myRight && x + step < screenHeight)
			car->setX(x + step);
	}
}

void Collision::setAction(vector<std::shared_ptr<Obstruction>> &elements, vector<std::shared_ptr<Car>> &Cars, vector<int> &actions) {
	int speed = freq / 10;
	int comboAction = myNoAction;
	
	for (auto & Car : Cars) {
		if (!actions.empty()) {
			int i = 0;
			while (i < actions.size() && actions[i] != myNoAction) {
				comboAction += actions[i++];
				if (comboAction == myLeftDown)
					cout << "myLeftDown\n";
				if (comboAction == myLeftUp)
					cout << "myLeftDown\n";
				if (comboAction == myRightDown)
					cout << "myRightDown\n";
				if (comboAction == myRightDown)
					cout << "myRightDown\n";
				actions.pop_back();
			}
			recalculateForSingleCar(Car, comboAction);
		}
	}
	moveRoadDown(elements, speed);
}

