#include "inputmanager.h"

#include <iostream>
#include <queue>

#include "../framework/window/window.h"
#include "../framework/input/mouse.h"
#include "../framework/system/event.h"

Purity::InputManager::InputManager(Purity::Window* window, std::queue<Event>* inputQueue)
{
    mWindow = window;
    mInputQueue = inputQueue;
}

void Purity::InputManager::update()
{
    Event event;

    while (mWindow->pollEvent(event))
    {
        mInputQueue->push(event);

        if (event.type == Event::Closed)
        {
            mWindow->close();
        }
        else if (event.type == Event::KeyPressed)
        {
            if (event.keyEvent.code == SDLK_ESCAPE)
            {
                mWindow->close();
            }
        }
        else if (event.type == Event::FocusGained)
        {
            mWindow->gainFocus();
        }
        else if (event.type == Event::FocusLost)
        {
            mWindow->loseFocus();
        }
    }
}
