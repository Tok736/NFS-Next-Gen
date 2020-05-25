//
// Created by margot on 12.05.2020.
//

#include "graphics/graphic.h"
#include "physics/physics.h"



FocusController fc ;

enum buttons{
    formB = 2,
    submitB = 3,
    exitB = 4,
    nothingPressed = 10,
};

void updateLoginView(const shared_ptr<sf::RenderWindow>& window, sf::Text &goToForm,
                        sf::Text &actionWithForm, sf::Text &exitFromGame)
{
    goToForm.setColor(sf::Color(255,255,255));
    actionWithForm.setColor(sf::Color(255,255,255));
    exitFromGame.setColor(sf::Color(255,255,255));

    if (isContain(window, goToForm))
    {
        goToForm.setColor(sf::Color(1,255,244));

    }
    //restart Game
    if (isContain(window, actionWithForm)) {
        actionWithForm.setColor(sf::Color(235, 230, 9));

    }
    //Exit
    if (isContain(window, exitFromGame)) {
        exitFromGame.setColor(sf::Color(82,43,255));
    }
}


void setBg(string &type,
        sf::Texture &menuBackground, sf::Text &goToForm, sf::Text &actionWithForm)
{
    if (type == "login") {
        menuBackground.loadFromFile("src/textures/login.png");
        goToForm.setString("registration");
        actionWithForm.setString("sign in");
    }
    else {
        menuBackground.loadFromFile("src/textures/registration.png");
        goToForm.setString("login");
        actionWithForm.setString("save");
    }
}



void buttonIsPressedForm(const shared_ptr<sf::RenderWindow>& window, const int& menuNum, sf::Sprite &menuBg,
        sf::Text &goToForm, sf::Text &actionWithForm, sf::Text &exitFromGame)
{

    renderPause(window, menuBg, goToForm, actionWithForm, exitFromGame);
    usleep(200000);
    window->clear();
    setSizeForButton(menuNum, goToForm, actionWithForm, exitFromGame, 20);
    renderPause(window, menuBg, goToForm, actionWithForm, exitFromGame);
    usleep(100000);
    setSizeForButton(menuNum, goToForm, actionWithForm, exitFromGame, 30);
    renderPause(window, menuBg, goToForm, actionWithForm, exitFromGame);
    window->clear();
}

pair<pair<string,string>,string>  displayLoginMenu(const shared_ptr<sf::RenderWindow>& window, string &type,  const string &errorMassage)
{

    sf::Font font ;
    font.loadFromFile("src/fonts/fontForScore.ttf");

    sf::Text goToForm;
    sf::Text actionWithForm;
    sf::Text exitFromGame("Exit", font, 40);
    exitFromGame.setPosition(screenWidth/2, screenHeight/1.45);

    sf::Text errorMes(errorMassage, font, 25);
    if (!errorMassage.empty()) {
        errorMes.setPosition(screenWidth/2.77, screenHeight/3.46);
        errorMes.setColor(sf::Color::Red);
    }

    sf::Texture menuBackground;
    setBg(type,menuBackground, goToForm, actionWithForm);

    goToForm.setFont(font);
    actionWithForm.setFont(font);
    goToForm.setCharacterSize(30);
    actionWithForm.setCharacterSize(40);
    goToForm.setPosition(screenWidth/24, screenHeight/1.43);
    actionWithForm.setPosition(screenWidth/2.77, screenHeight/1.84);
    goToForm.setColor(sf::Color::White);
    actionWithForm.setColor(sf::Color::White);



    sf::Sprite menuBg(menuBackground);
    menuBg.setPosition(0,0);

    sf::Text login, password;
    login.setPosition ( screenWidth/3.9, screenHeight/3.1 ) ;
    password.setPosition ( screenWidth/3.9 , screenHeight/2.3 ) ;
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


    int menuNum = 0;

    while (window->isOpen() && !pressButton)
    {
        sf::Event event{};
        while (window->pollEvent(event))
        {
            updateLoginView(window, goToForm, actionWithForm, exitFromGame);
            if ( sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (isContain(window, goToForm))
                {
                    menuNum = formB;
                    if (type == "login")
                        type = "registration";
                    else
                        type = "login";
                    errorMes.setString("");
                    setBg(type,menuBackground, goToForm, actionWithForm);
                    buttonIsPressedForm(window,menuNum,menuBg, goToForm, actionWithForm, exitFromGame);
                }

                if (sf::IntRect(screenWidth/3.9, screenHeight/3.1 , screenWidth/3.33,screenHeight/15).contains(sf::Mouse::getPosition(*window)))
                {
                    fc.setFocusObject( &tbLogin ) ;
                }
                else if (sf::IntRect(screenWidth/3.9, screenHeight/2.3, screenWidth/3.33,screenHeight/15).contains(sf::Mouse::getPosition(*window))){
                    fc.setFocusObject( &tbPassw ) ;
                }
                else if (isContain(window, actionWithForm)){
                    data.first.first = tbLogin.getText().getString();
                    data.first.second = tbPassw.getText().getString();
                    data.second = type;
                    menuNum = submitB;
                    buttonIsPressedForm(window,menuNum,menuBg, goToForm, actionWithForm, exitFromGame);
                    pressButton = true;
                }
                else if(isContain(window, exitFromGame) || event.type == sf::Event::Closed) {
                    data.second = "exit";
                    menuNum = exitB;
                    buttonIsPressedForm(window,menuNum,menuBg, goToForm, actionWithForm, exitFromGame);
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
        window->draw(goToForm);
        window->draw(exitFromGame);
        window->draw(actionWithForm);
        window->draw ( tbLogin ) ;
        window->draw ( tbPassw ) ;
        if (!errorMassage.empty())
            window->draw(errorMes);
        window->display();
    }

    return data;
}