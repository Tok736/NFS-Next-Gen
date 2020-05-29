//
// Created by margot on 12.05.2020.
//

#include "graphics/graphic.h"
#include "physics/physics.h"



FocusController fc ;

enum buttons{
    formB = 1,
    submitB = 2,
    exitB = 0,
    nothingPressed = 10,
};

enum buttonsSize
{
    beforePress = 30,
    afterPress = 20,
    exitAndActionSize = 40,
    errorMesSize = 25,
    loginAndPasswLetter = 48,
};


constexpr pair<float, float> exitFromGamePos {screenWidth/2, screenHeight/1.45};
constexpr pair<float, float> errorMesPos {screenWidth/2.77, screenHeight/3.46};
constexpr pair<float, float> goToFormPos {screenWidth/24, screenHeight/1.43};
constexpr pair<float, float> actionWithFormPos {screenWidth/2.77, screenHeight/1.84};
constexpr pair<float, float> loginPos {screenWidth/3.9, screenHeight/3.1};
constexpr pair<float, float> passwordPos {screenWidth/3.9 , screenHeight/2.3};
constexpr pair<float, float> loginInputPos {screenWidth/3.9, screenHeight/3.1};
constexpr pair<float, float> loginAndPassInputSize {screenWidth/3.33,screenHeight/15};
constexpr pair<float, float> PasswInputPos { screenWidth/3.9, screenHeight/2.3};


void updateLoginView(const shared_ptr<sf::RenderWindow>& window, sf::Text &goToForm,
                        sf::Text &actionWithForm, sf::Text &exitFromGame)
{
    goToForm.setFillColor(sf::Color::White);
    actionWithForm.setFillColor(sf::Color::White);
    exitFromGame.setFillColor(sf::Color::White);

    if (isContain(window, goToForm))
    {
        goToForm.setFillColor(sf::Color(1,255,244));

    }
    //restart Game
    if (isContain(window, actionWithForm)) {
        actionWithForm.setFillColor(sf::Color(235, 230, 9));

    }
    //Exit
    if (isContain(window, exitFromGame)) {
        exitFromGame.setFillColor(sf::Color(82,43,255));
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
    setSizeForButton(menuNum, goToForm, actionWithForm, exitFromGame, afterPress);
    renderPause(window, menuBg, goToForm, actionWithForm, exitFromGame);
    usleep(100000);
    setSizeForButton(menuNum, goToForm, actionWithForm, exitFromGame, beforePress);
    renderPause(window, menuBg, goToForm, actionWithForm, exitFromGame);
    window->clear();
}

pair<pair<string,string>,string>  displayLoginMenu(const shared_ptr<sf::RenderWindow>& window, string &type,  const string &errorMassage)
{

    sf::Font font ;
    font.loadFromFile("src/fonts/fontForScore.ttf");

    sf::Text goToForm;
    sf::Text actionWithForm;
    sf::Text exitFromGame("Exit", font, exitAndActionSize);
    exitFromGame.setPosition(exitFromGamePos.first, exitFromGamePos.second);

    sf::Text errorMes(errorMassage, font, errorMesSize);
    if (!errorMassage.empty()) {
        errorMes.setPosition(errorMesPos.first, errorMesPos.second);
        errorMes.setFillColor(sf::Color::Red);
    }

    sf::Texture menuBackground;
    setBg(type,menuBackground, goToForm, actionWithForm);

    goToForm.setFont(font);
    actionWithForm.setFont(font);
    goToForm.setCharacterSize(beforePress);
    actionWithForm.setCharacterSize(exitAndActionSize);
    goToForm.setPosition(goToFormPos.first, goToFormPos.second);
    actionWithForm.setPosition(actionWithFormPos.first, actionWithFormPos.second);
    goToForm.setFillColor(sf::Color::White);
    actionWithForm.setFillColor(sf::Color::White);



    sf::Sprite menuBg(menuBackground);
    menuBg.setPosition(leftAngle,leftAngle);

    sf::Text login, password;
    login.setPosition ( loginPos.first, loginPos.second) ;
    password.setPosition ( passwordPos.first, passwordPos.second ) ;
    login.setFont ( font ) ;
    password.setFont ( font ) ;
    login.setCharacterSize(loginAndPasswLetter);
    password.setCharacterSize(loginAndPasswLetter);
    login.setString ( "" ) ;
    password.setString ( "" ) ;
    TextBox tbLogin ( login ) ;
    TextBox tbPassw ( password ) ;

    fc.setFocusObject( &tbLogin ) ;


    pair<pair<string, string>, string>data;

    bool pressButton = false;


    int menuNum = nothingPressed;

    while (window->isOpen() && !pressButton)
    {
        sf::Event event{};
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
                data.second = "exit";
                pressButton = true;
            }
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

                if (sf::IntRect(loginInputPos.first, loginInputPos.second , loginAndPassInputSize.first, loginAndPassInputSize.second).contains(sf::Mouse::getPosition(*window)))
                {
                    fc.setFocusObject( &tbLogin ) ;
                }
                else if (sf::IntRect(PasswInputPos.first, PasswInputPos.second, loginAndPassInputSize.first, loginAndPassInputSize.second).contains(sf::Mouse::getPosition(*window))){
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