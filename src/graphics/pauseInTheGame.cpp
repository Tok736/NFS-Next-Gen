//
// Created by margot on 11.05.2020.
//

#include "graphics/graphic.h"
#include "physics/physics.h"

bool pauseWindow(std::shared_ptr<Window> &window,const int &timeInGame)
{
    Window::createRenderWindow(window, screenWidth, screenHeight, "Pause");
    return isPause(window, timeInGame);
}

bool isPause(std::shared_ptr<Window> &window,const int &timeInGame)
{
    return false;
}