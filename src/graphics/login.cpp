//
// Created by margot on 12.05.2020.
//

#include "graphics/graphic.h"
#include "physics/physics.h"




FocusController fc ;

pair<pair<string,string>,string>  displayLoginMenu(const shared_ptr<sf::RenderWindow>& window, string &type)
{

    return isLogin(window,type);
}

pair<pair<string,string>,string>  isLogin(const shared_ptr<sf::RenderWindow>& window, string &type)
{
//    Window::createRenderWindow(window, screenWidth, screenHeight, "Login");
//    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), L"Login");

    sf::Font font ;
    font.loadFromFile("src/fonts/fontForScore.ttf");

    sf::Texture menuBackground;
    if (type == "login")
        menuBackground.loadFromFile("src/textures/login.png");
    else
        menuBackground.loadFromFile("src/textures/registration.png");

    sf::Sprite menuBg(menuBackground);
    menuBg.setPosition(0,0);

    sf::Text login, password;
    login.setPosition ( 370, 292 ) ;
    password.setPosition ( 370 , 394 ) ;
    login.setFont ( font ) ;
    password.setFont ( font ) ;
    login.setCharacterSize(48);
    password.setCharacterSize(48);
    login.setString ( "" ) ;
    password.setString ( "" ) ;
    TextBox tbLogin ( login ) ;
    TextBox tbPassw ( password ) ;

    fc.setFocusObject( &tbLogin ) ;


    pair<pair<string, string>, string>data;

    bool pressButton = false;

    while (window->isOpen() && !pressButton)
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed) {
                type = "exit";
                window->close();
            }
            if ( event.type == sf::Event::MouseButtonPressed )
            {
                if (sf::IntRect(60, 604, 224, 23).contains(sf::Mouse::getPosition(*window)) && type == "login")
                {
                    type = "registration";
                    menuBackground.loadFromFile("src/textures/registration.png");
                }
                if (sf::IntRect(60, 604, 130, 23).contains(sf::Mouse::getPosition(*window)) && type == "registration")
                {
                    type = "login";
                    menuBackground.loadFromFile("src/textures/login.png");
                }
                if (sf::IntRect(370, 292 , 433,60).contains(sf::Mouse::getPosition(*window)))
                {
                    fc.setFocusObject( &tbLogin ) ;
                }
                else if (sf::IntRect(370, 391, 433,60).contains(sf::Mouse::getPosition(*window))){
                    fc.setFocusObject( &tbPassw ) ;
                }
                else if (sf::IntRect(583, 488, 217,79).contains(sf::Mouse::getPosition(*window))){
                    data.first.first = tbLogin.getText().getString();
                    data.first.second = tbPassw.getText().getString();
                    data.second = type;
                    pressButton = true;
                }
            }
            FocusObject * fo = fc.getFocusObject() ;
            if ( fo!= nullptr )
            {
                fo->event ( event ) ;
            }
        }
        window->clear();
        window->draw(menuBg);
        window->draw ( tbLogin ) ;
        window->draw ( tbPassw ) ;
        window->display();
    }

    return data;
}