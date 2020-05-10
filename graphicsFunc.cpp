//
// Created by margot on 02.05.2020.
//

#include "graphic.h"
#include <sstream>

void Clock::restart() {
	clock_.restart();
}

float Clock::getClockMicro() {
	return clock_.getElapsedTime().asMicroseconds();
}


float Clock::getClockSec() {
	return clock_.getElapsedTime().asSeconds();
}


void Window::createRenderWindow(shared_ptr<Window> miniEngine, float width, float height, const std::string &title) {
    shared_ptr<sf::RenderWindow> newWindow(new sf::RenderWindow(sf::VideoMode((unsigned int) width, (unsigned int) height), title));
	miniEngine->renderWindow_= newWindow;
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


template <typename T>
std::string toString(T val)
{
    std::ostringstream oss;
    oss<<val;
    return oss.str();
}

//void Window::render(const std::vector<Car> &cars, const std::vector<Obstruction> &roadElements, int actions) {
void Window::render( std::vector<Car> cars,  std::vector<Obstruction> roadElements, int actions, float timeInGame) {
    renderWindow_->clear();
    sf::Texture roadTexture1, roadTexture2;
    roadTexture1.loadFromFile("/home/margot/testGame/testAll/textures/littleRoad.png");
    roadTexture2.loadFromFile("/home/margot/testGame/testAll/textures/littleRoad.png");
    sf::Sprite roadSprite1(roadTexture1);
    sf::Sprite roadSprite2(roadTexture2);

    if (roadElements.size() >= 2) {
        roadSprite1.setPosition((float) roadElements[0].getX(), (float) roadElements[0].getY());
        roadSprite2.setPosition((float) roadElements[1].getX(), (float) roadElements[1].getY());
        renderWindow_->draw(roadSprite1);
        renderWindow_->draw(roadSprite2);
    }
    for (auto &car : cars) {
        sf::Texture carTexture;
        if (actions != -1) {
            if (actions == myUp)
                carTexture.loadFromFile("/home/margot/testGame/testAll/textures/Car_1.png");
            else if (actions == myDown)
                carTexture.loadFromFile("/home/margot/testGame/testAll/textures/Car_0.png");
            else if (actions == myLeft)
                carTexture.loadFromFile("/home/margot/testGame/testAll/textures/Car_4.png");
            else if (actions == myRight)
                carTexture.loadFromFile("/home/margot/testGame/testAll/textures/Car_6.png");
        } else
            carTexture.loadFromFile("/home/margot/testGame/testAll/textures/Car_0.png");
        sf::Sprite carSprite(carTexture);
        carSprite.setPosition((float) car.getX(), (float) car.getY());
        renderWindow_->draw(carSprite);
    }

    sf::RectangleShape scoreShape(sf::Vector2f(screenWidth/3 - 20, screenWidth/10));
    scoreShape.move(2 * screenWidth / 3 - 5, 10);
    scoreShape.setFillColor(sf::Color(0, 0, 0, 50));
    renderWindow_->draw(scoreShape);
    sf::Font font;
    font.loadFromFile("/home/margot/testGame/testAll/fonts/fontForScore.ttf");
    sf::Text score("", font, 20);
    score.setFillColor(sf::Color(255, 255, 255));
    score.setString("Score: " + toString(timeInGame));
    score.setPosition(2*screenWidth/3, screenWidth/20);
    renderWindow_->draw(score);
}

void Window::display() {
	renderWindow_->display();
}

void Window::close() {
	renderWindow_->close();
}

void Window::clear() {
    renderWindow_->clear();
}

void Window::draw(sf::Sprite &toDraw) {
    renderWindow_->draw(toDraw);
}

shared_ptr<sf::RenderWindow> Window::getWindow() {
    return renderWindow_;
}

bool Window::pollEvent(sf::Event& event) {
    renderWindow_->pollEvent(event);
    return true;
}

shared_ptr<sf::RenderWindow> Window::getRenderWindow() {
    return renderWindow_;
}

unsigned int Window::getWidth() const {
    return width_;
}

unsigned int Window::getHeight() const {
    return height_;
}


bool displayMenu(std::shared_ptr<Window> &window)
{
    Window::createRenderWindow(window, screenWidth, screenHeight, "Menu");
    return isMenu(window);
}

bool isMenu(std::shared_ptr<Window> &window)
{
    sf::Texture buttonStart, buttonStartPress, nameOfGame, menuBackground;
    buttonStart.loadFromFile("/home/margot/testGame/testAll/textures/buttonStart.png");
    buttonStartPress.loadFromFile("/home/margot/testGame/testAll/textures/buttonStartPress.png");
    menuBackground.loadFromFile("/home/margot/testGame/testAll/textures/menu.png");
    nameOfGame.loadFromFile("/home/margot/testGame/testAll/textures/nameOfGame.png");
    sf::Sprite menu1(buttonStart), menuBg(menuBackground), gameName(nameOfGame);
    int menuNum = 0;
    int start = 0;
    menu1.setPosition(screenWidth/2-90, screenHeight/2-50);
    menuBg.setPosition(0,0);
    gameName.setPosition(screenWidth/4, screenHeight/8);

    float xProcentUpdate = 1;
    float yProcentUpdate = 1;

    sf::Event event;
    while (!start)
    {
        menu1.setTexture(buttonStart);
        menuNum = 0;
        window->clear();
        if (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            {
                window->close();
                return false;
            }
            if (event.type == sf::Event::Resized)
            {
                window->setHeight(static_cast<unsigned int>(event.size.height));
                window->setWidth(static_cast<unsigned int>(event.size.width));
                xProcentUpdate = window->getWidth()/screenWidth;
                yProcentUpdate = window->getHeight()/screenHeight;
                if (yProcentUpdate == 0)
                    yProcentUpdate = 1;
                if (xProcentUpdate == 0)
                    xProcentUpdate = 1;
            }
            if (sf::IntRect(window->getWidth()/ 2 - 90*xProcentUpdate, window->getHeight()/ 2 - 50*yProcentUpdate, 200*xProcentUpdate, 90*yProcentUpdate).contains(
                    sf::Mouse::getPosition(*window->getWindow()))) {
                menu1.setTexture(buttonStartPress);
                menuNum = 1;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (menuNum == 1) {
                    window->clear();
                    start = 1;
                }
            }
        }
        window->draw(menuBg);
        window->draw(menu1);
        window->draw(gameName);

        window->display();
    }
    return true;
};
