#include "physics.h"
#include <iostream>

void createIGameElements() {
	vector<shared_ptr< Obstruction>> elements;
	Car car1;
	
	car1.setUserId(1);
	car1.setX(0);
	car1.setY(0);
	for(int i = 0; i < 5; ++i) {
		Obstruction obstr;
		obstr.setX(i);
		obstr.setY(i);
		obstr.setId(i);
		elements.push_back(std::make_shared<Obstruction>(obstr));
	}
	
}

int main() {
	createIGameElements();
	return 0;
}

