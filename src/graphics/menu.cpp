//
// Created by margot on 02.05.2020.
//

#include "graphics/graphic.h"
#include "phisics/physics.h"

bool displayMenu()
{
    shared_ptr<Window> window(new Window);
    Window::createRenderWindow(window, screenLength, screenWidth, "Menu");
    return isMenu(window);
}

bool isMenu(std::shared_ptr<Window> &window)
{
    sf::Texture buttonStart, buttonStartPress, nameOfGame, menuBackground;
    buttonStart.loadFromFile("src/textures/buttonStart.png");
    buttonStartPress.loadFromFile("src/textures/buttonStartPress.png");
    menuBackground.loadFromFile("src/textures/menu.png");
    nameOfGame.loadFromFile("src/textures/nameOfGame.png");
    sf::Sprite menu1(buttonStart), menuBg(menuBackground), gameName(nameOfGame);
    int menuNum = 0;
    menu1.setPosition(screenLength/2-90, screenWidth/2-50);
    menuBg.setPosition(0,0);
    gameName.setPosition(screenLength/4, screenWidth/8);

    sf::Event event;
    while (window->isOpen())
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
            else if (sf::IntRect(screenLength / 2 - 90, screenWidth / 2 - 50, 200, 90).contains(
                    sf::Mouse::getPosition(*window->getWindow()))) {
                menu1.setTexture(buttonStartPress);
                menuNum = 1;
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (menuNum == 1)
                    window->close();
            }
        }
        window->draw(menuBg);
        window->draw(menu1);
        window->draw(gameName);

        window->display();
    }
    return true;
};

