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

    mWindowPos = mWindow->getPosition();
    mWindowSize = mWindow->getSize();

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
        else if (event.type == Event::Resized)
        {
            if (mWindow->forceAspectRatio())
            {
                mMustHandleWindowResize = true;
            }
        }


        if (mWindow->isContentMode() && !mModeLock)
        {
            mInputQueue->push(event);
        }
    }

    if (mMustHandleWindowResize)
    {
        handleWindowResize();
        mMustHandleWindowResize = false;
    }
}

void Purity::InputManager::handleWindowResize()
{
    auto newWindowSize = mWindow->getSize();
    auto newWindowPos = mWindow->getPosition();
    std::cout << newWindowSize.x << std::endl;

    // right
    if ((newWindowSize.x != mWindowSize.x) && (mWindowPos == newWindowPos))
    {
        newWindowSize.y += (newWindowSize.x - mWindowSize.x);
    }
    //bottom
    else if ((newWindowSize.y != mWindowSize.y) && (mWindowPos == newWindowPos))
    {
        newWindowSize.x += (newWindowSize.y - mWindowSize.y);
    }
    //left
    else if ((newWindowSize.x != mWindowSize.x) && (mWindowPos != newWindowPos))
    {
        newWindowSize.y += (newWindowSize.x - mWindowSize.x);
    }
    //top
    else
    {
        newWindowSize.x += (newWindowSize.y - mWindowSize.y);
    }

    std::cout << newWindowSize.x << std::endl;

    mWindow->setSize(newWindowSize);
}
