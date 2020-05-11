//
// Created by margot on 02.05.2020.
//


#include "graphics/graphic.h"
#include "physics/physics.h"

#define obstractX 56
#define obstractY 56
#define carX carHeight/2
#define carY carLength/2

/////////////////////                    CLOCK            //////////////////////////////////////////

void Clock::restart() {
    clock_.restart();
}


float Clock::getClockMicro() {
    return clock_.getElapsedTime().asMicroseconds();
}


float Clock::getClockSec() {
    return clock_.getElapsedTime().asSeconds();
}


/////////////////////                    WINDOW            //////////////////////////////////////////

void Window::createRenderWindow(shared_ptr<Window> miniEngine, unsigned int width, unsigned int height, const std::string &title) {
    shared_ptr<sf::RenderWindow> newWindow(new sf::RenderWindow(sf::VideoMode(width, height), title));
    miniEngine->renderWindow_= newWindow;
    miniEngine->setHeight(height);
    miniEngine->setWidth(width);

}

void Window::setWidth(unsigned int width) {
    width_ = width;
}

void Window::setHeight(unsigned int height) {
    height_ = height;
}

bool Window::isOpen() {
    return renderWindow_->isOpen();
}

void Window::handleEvents(std::vector<int> &actions) {
    sf::Event event{};
    while (renderWindow_->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            actions.push_back(endOfTheGame);
            return;
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Right)
                actions.push_back(myRight);
            if (event.key.code == sf::Keyboard::Left)
                actions.push_back(myLeft);
            if (event.key.code == sf::Keyboard::Up)
                actions.push_back(myUp);
            if (event.key.code == sf::Keyboard::Down)
                actions.push_back(myDown);
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {

        }
        else break;
    }
}


void Window::createTextures(std::vector<Car> &cars, std::vector<Obstruction> &roadAndObstcl) {

    for (auto & car : cars)
    {
        sf::Texture tempTextureCar;
        std::vector<sf::Texture> tempVectorOfTextures;
        for (int i=0; i<4; i++)
        {
            tempTextureCar.loadFromFile("src/textures/CarAction_"+toString(i)+".png");
            tempVectorOfTextures.push_back(tempTextureCar);
        }
        mapOfRextures.insert(std::pair<int, std::vector<sf::Texture>>(car.getId(), tempVectorOfTextures));
    }

    for (auto & roadElem : roadAndObstcl)
    {
        sf::Texture tempTexture;
        std::vector<sf::Texture> tempVectorOfTextures;
        if (roadElem.getId()== 0 || roadElem.getId() == 1)
        {
            tempTexture.loadFromFile("src/textures/littleRoad.png");
            tempVectorOfTextures.push_back(tempTexture);
        } else{
            tempTexture.loadFromFile("src/textures/obstruction" + toString(roadElem.getId())+ ".png");
            tempVectorOfTextures.push_back(tempTexture);
        }
        mapOfRextures.insert(std::pair<int, std::vector<sf::Texture>>(roadElem.getId(), tempVectorOfTextures));
    }
}

void Window::render(std::vector<Car> &cars,  std::vector<Obstruction> &roadElements, int &actions, int &timeInGame) {
    renderWindow_->clear();

    sf::Sprite roadSprite1(mapOfRextures.find(roadElements[0].getId())->second[0]);
    sf::Sprite roadSprite2(mapOfRextures.find(roadElements[1].getId())->second[0]);


    if (roadElements.size() >= 2 ) {

        roadSprite1.setPosition(0, (float) roadElements[0].getY());
        roadSprite2.setPosition(0, (float) roadElements[1].getY());
        renderWindow_->draw(roadSprite1);
        renderWindow_->draw(roadSprite2);
    }

//    if (timeInGame)

    auto iterRoad = roadElements.begin()+2;
    for (; iterRoad!=roadElements.end(); iterRoad++)
    {
        sf::Sprite roadObstract(mapOfRextures.find((*iterRoad).getId())->second[0]);
        roadObstract.setPosition((float) (*iterRoad).getX() - obstractX, (float) (*iterRoad).getY() - obstractY);
        renderWindow_->draw(roadObstract);
    }


    for (auto &car : cars) {
        sf::Sprite carSprite;
        if (actions != myNoAction)
        {
            if (actions == myUp)
                carSprite.setTexture(mapOfRextures.find(car.getId())->second[1]);
            else if (actions == myDown)
                carSprite.setTexture(mapOfRextures.find(car.getId())->second[0]);
            else if (actions == myLeft)
                carSprite.setTexture(mapOfRextures.find(car.getId())->second[2]);
            else if (actions == myRight)
                carSprite.setTexture(mapOfRextures.find(car.getId())->second[3]);
        }
        else
            carSprite.setTexture(mapOfRextures.find(car.getId())->second[0]);

        carSprite.setPosition((float) car.getX() - carX, (float) car.getY() + carY);
        renderWindow_->draw(carSprite);
    }

    sf::RectangleShape scoreShape(sf::Vector2f(screenWidth/3 - 20, screenHeight/10));
    scoreShape.move(2*screenWidth/3+5, 10);
    scoreShape.setFillColor(sf::Color(0,0,0,50));
    renderWindow_->draw(scoreShape);
    sf::Font font;
    font.loadFromFile("src/fonts/fontForScore.ttf");
    sf::Text score("", font, 20);
    score.setFillColor(sf::Color(255,255,255));
    score.setString("Score: " + toString<int>(timeInGame));
    score.setPosition(2*screenWidth/3+5, screenHeight/20);
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

