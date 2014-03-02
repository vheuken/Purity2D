#include "inputmanager.h"

#include <iostream>
#include <queue>

#include "../framework/window.h"

Purity::InputManager::InputManager(Purity::Window* window, std::queue<sf::Event>* inputQueue)
{
    mWindow = window;
    mInputQueue = inputQueue;
}

void Purity::InputManager::update()
{
    sf::Event event;

    while (mWindow->pollEvent(event))
    {
        mInputQueue->push(event);

        if (event.type == sf::Event::Closed)
        {
            mWindow->close();
        }
    }

    mWindow->manipulateWindow();
}
