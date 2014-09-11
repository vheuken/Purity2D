#include "inputmanager.h"

#include <iostream>
#include <queue>

#include "../framework/window/window.h"
#include "../framework/input/mouse.h"
#include "../framework/system/event.h"

Purity::InputManager::InputManager(Purity::Window* window, std::queue<Event>* inputQueue)
    : mModeLock(false)
{
    mWindow = window;
    mInputQueue = inputQueue;
}

void Purity::InputManager::update()
{
    Event event;

    while (mWindow->pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            if (!mWindow->isContentMode())
            {
                mWindow->close();
            }
        }
        else if (event.type == Event::KeyPressed)
        {
            if (event.keyEvent.code == SDLK_ESCAPE)
            {
                if (!mWindow->isContentMode())
                {
                    mWindow->close();
                }
            }
            else if (event.keyEvent.code == SDLK_BACKSPACE)
            {
                if (!mModeLock)
                {
                    mWindow->toggleMode();
                    mModeLock = true;
                }
            }
        }
        else if (event.type == Event::KeyReleased)
        {
            if (event.keyEvent.code == SDLK_BACKSPACE)
            {
                if (mModeLock)
                {
                    mModeLock = false;
                }
            }
        }
        else if (event.type == Event::FocusGained)
        {
            mWindow->gainFocus();
        }
        else if (event.type == Event::FocusLost)
        {
            mWindow->loseFocus();
            mWindow->setWindowMode();
        }

        if (mWindow->isContentMode() && !mModeLock)
        {
            mInputQueue->push(event);
        }
    }
}
