//
// Created by margot on 02.05.2020.
//

#include "graphic.h"

void Clock::restart() {
	clock_.restart();
}

float Clock::getClockMicro() {
	return clock_.getElapsedTime().asMicroseconds();
}


float Clock::getClockSec() {
	return clock_.getElapsedTime().asSeconds();
}


void Window::createRenderWindow(Window *miniEngine, float width, float height, const std::string &title) {
	miniEngine->renderWindow_ = new sf::RenderWindow(sf::VideoMode((unsigned int) width, (unsigned int) height), title);
	miniEngine->setHeight(height);
	miniEngine->setWidth(width);
}

void Window::setWidth(float width) {
	width_ = width;
}

void Window::setHeight(float height) {
	height_ = height;
}

bool Window::isOpen() {
	return renderWindow_->isOpen();
}

void Window::handleEvents(std::vector<int> &actions) {
	sf::Event event{};
	if (renderWindow_->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			actions.push_back(endOfTheGame);
			return;
		}
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Right)
				actions.push_back(myRight);
			if (event.key.code == sf::Keyboard::Left)
				actions.push_back(myLeft);
			if (event.key.code == sf::Keyboard::Up)
				actions.push_back(myUp);
			if (event.key.code == sf::Keyboard::Down)
				actions.push_back(myDown);
		}
	}
}


void Window::render(std::vector<Car> cars, std::vector<Obstruction> roadElements) {
	renderWindow_->clear();
	for (auto &car : cars) {
		sf::Texture carTexture, roadTexture1, roadTexture2;
		carTexture.loadFromFile("/home/vlad/forUml/textures/Car_0.png");
		roadTexture1.loadFromFile("/home/vlad/forUml/textures/littleRoad.png");
		roadTexture2.loadFromFile("/home/vlad/forUml/textures/littleRoad.png");
		sf::Sprite roadSprite1(roadTexture1);
		sf::Sprite roadSprite2(roadTexture2);
		sf::Sprite carSprite(carTexture);
		roadSprite1.setPosition((float) roadElements[0].getX(), (float) roadElements[0].getY());
		roadSprite2.setPosition((float) roadElements[1].getX(), (float) roadElements[1].getY());
		carSprite.setPosition((float) car.getX(), (float) car.getY());
		renderWindow_->draw(roadSprite1);
		renderWindow_->draw(roadSprite2);
		renderWindow_->draw(carSprite);
	}
}

void Window::display() {
	renderWindow_->display();
}

void Window::close() {
	renderWindow_->close();
}