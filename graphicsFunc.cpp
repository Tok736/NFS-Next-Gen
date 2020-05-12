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
void Window::render(std::vector<Car> &cars,  std::vector<Obstruction> &roadElements, int &actions, int &timeInGame) {
    renderWindow_->clear();
    sf::Texture roadTexture1, roadTexture2, obstruct;
    roadTexture1.loadFromFile("/home/purplelime/tp_project_1sem/NFS-Next-Gen/textures/littleroad.jpg");
    roadTexture2.loadFromFile("/home/purplelime/tp_project_1sem/NFS-Next-Gen/textures/littleroad.jpg");
	obstruct.loadFromFile("//home/purplelime/tp_project_1sem/NFS-Next-Gen/textures/rock1-min.png");
    sf::Sprite roadSprite1(roadTexture1);
    sf::Sprite roadSprite2(roadTexture2);
	sf::Sprite roadObstract(obstruct);

    if (roadElements.size() >= 2) {
    	roadObstract.setPosition((float) roadElements[2].getX(), (float) roadElements[2].getY());
        roadSprite1.setPosition((float) roadElements[0].getX(), (float) roadElements[0].getY());
        roadSprite2.setPosition((float) roadElements[1].getX(), (float) roadElements[1].getY());
        renderWindow_->draw(roadSprite1);
        renderWindow_->draw(roadSprite2);
		renderWindow_->draw(roadObstract);
    }
    for (auto &car : cars) {
        sf::Texture carTexture;
        if (actions != myNoAction) {
            if (actions == myUp)
                carTexture.loadFromFile("/home/purplelime/tp_project_1sem/NFS-Next-Gen/textures/Car_1.png");
            else if (actions == myDown)
                carTexture.loadFromFile("/home/purplelime/tp_project_1sem/NFS-Next-Gen/textures/Car_0.png");
            else if (actions == myLeft)
                carTexture.loadFromFile("/home/purplelime/tp_project_1sem/NFS-Next-Gen/textures/Car_4.png");
            else if (actions == myRight)
                carTexture.loadFromFile("/home/purplelime/tp_project_1sem/NFS-Next-Gen/textures/Car_6.png");
        } else
            carTexture.loadFromFile("/home/purplelime/tp_project_1sem/NFS-Next-Gen/textures/Car_0.png");
        sf::Sprite carSprite(carTexture);
        carSprite.setPosition((float) car.getX(), (float) car.getY());
        renderWindow_->draw(carSprite);
    }

    sf::RectangleShape scoreShape(sf::Vector2f(screenWidth/3 - 20, screenHeight/10));
    scoreShape.move((float)100*screenWidth/137 - 5, 10);
    scoreShape.setFillColor(sf::Color(0, 0, 0, 50));
    renderWindow_->draw(scoreShape);
    sf::Font font;
    font.loadFromFile("/home/purplelime/tp_project_1sem/NFS-Next-Gen/fonts/fontForScore.ttf");
    sf::Text score("", font, 20);
    score.setFillColor(sf::Color(255, 255, 255));
    score.setString("Score: " + toString(timeInGame));
    score.setPosition(100*screenWidth/137, screenHeight/20);
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

void Window::draw(sf::Text &toDraw) {
    renderWindow_->draw(toDraw);
}


short int displayMenu(std::shared_ptr<Window> &window)
{
    Window::createRenderWindow(window, screenWidth, screenHeight, "Menu");
    return isMenu(window);
}

short int isMenu(std::shared_ptr<Window> &window)
{
    sf::Texture menuBackground;
    menuBackground.loadFromFile("/home/purplelime/tp_project_1sem/NFS-Next-Gen/textures/bg.png");
    sf::Sprite menuBg(menuBackground);
    int menuNum = 0;
    int start = 0;
    menuBg.setPosition(0,0);
    float xProcentUpdate = 1;
    float yProcentUpdate = 1;

    window->setWidth(screenWidth);
    window->setHeight(screenHeight);

    sf::Font font;
    font.loadFromFile("/home/purplelime/tp_project_1sem/NFS-Next-Gen/fonts/fontForScore.ttf");
    sf::Text singleGame("Single game", font, 60), coopGame("Online game", font, 60), exitFromGame("Exit", font, 60);
    singleGame.setFillColor(sf::Color(255,255,255));
    coopGame.setFillColor(sf::Color(255,255,255));
    exitFromGame.setFillColor(sf::Color(255,255,255));
    singleGame.setPosition(screenWidth/9, screenHeight/3);
    coopGame.setPosition(screenWidth/9, 4*screenHeight/9);
    exitFromGame.setPosition(screenWidth/9, 5*screenHeight/9);
    window->draw(singleGame);
    window->draw(coopGame);
    window->draw(exitFromGame);

    sf::Event event;
    while (!start)
    {
        singleGame.setFillColor(sf::Color(255,255,255));
        coopGame.setFillColor(sf::Color(255,255,255));
        exitFromGame.setFillColor(sf::Color(255,255,255));
        menuNum = 0;
        window->clear();
        if (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
                return 0;
            }
            if (event.type == sf::Event::Resized)
            {
                window->setHeight(static_cast<unsigned int>(event.size.height));
                window->setWidth(static_cast<unsigned int>(event.size.width));
                xProcentUpdate = (float)window->getWidth()/screenWidth;
                yProcentUpdate = (float)window->getHeight()/screenHeight;
                if (yProcentUpdate == 0)
                    yProcentUpdate = 1;
                if (xProcentUpdate == 0)
                    xProcentUpdate = 1;
            }
            //Single Game
            if (sf::IntRect((float)window->getWidth()/ 9 - xProcentUpdate, (float)window->getHeight()/3 + 30*yProcentUpdate, 400*xProcentUpdate, 90*yProcentUpdate).contains(
                    sf::Mouse::getPosition(*window->getWindow()))) {
                singleGame.setFillColor(sf::Color(83,15,173));
                menuNum = 2;
            }
            //Coop Game
            if (sf::IntRect((float)window->getWidth()/ 9 - xProcentUpdate, (float)4*window->getHeight()/9 + 30*yProcentUpdate, 400*xProcentUpdate, 90*yProcentUpdate).contains(
                    sf::Mouse::getPosition(*window->getWindow()))) {
                coopGame.setFillColor(sf::Color(255,0,173));
                menuNum = 3;
            }
            //Exit
            if (sf::IntRect((float)window->getWidth()/ 9 - xProcentUpdate, (float)5*window->getHeight()/9 + 30*yProcentUpdate, 200*xProcentUpdate, 90*yProcentUpdate).contains(
                    sf::Mouse::getPosition(*window->getWindow()))) {
                exitFromGame.setFillColor(sf::Color(240,73,60));
                menuNum = 4;
            }
            //handle Pressed Button
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                //pressed Single Game
                if (menuNum == 2) {
                    singleGame.setCharacterSize(40);
                    window->draw(menuBg);
                    window->draw(singleGame);
                    window->draw(coopGame);
                    window->draw(exitFromGame);
                    window->display();
                    window->clear();
                    return 1; //single
                }
                if (menuNum == 3)
                {
                    //coop
                    return 2;
                }
                //pressed Exit
                if (menuNum == 4)
                {
                    exitFromGame.setCharacterSize(40);
                    window->draw(menuBg);
                    window->draw(singleGame);
                    window->draw(coopGame);
                    window->draw(exitFromGame);
                    window->display();
                    window->close();
                    return 0;
                }
            }
        }
        window->draw(menuBg);
        window->draw(singleGame);
        window->draw(coopGame);
        window->draw(exitFromGame);
        window->display();
    }
    return 0;
};
