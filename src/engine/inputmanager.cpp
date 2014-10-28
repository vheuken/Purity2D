#include "inputmanager.h"

#include <iostream>
#include <queue>

#include <lua.hpp>
#include <LuaBridge.h>
#include "luamanager.h"

#include "../framework/scene.h"
#include "../framework/window/window.h"
#include "../framework/input/mouse.h"
#include "../framework/system/event.h"

Purity::InputSystem::InputSystem(Purity::Window* window,
                                 std::queue<Event>* inputQueue)
    : mModeLock(false)
{
    mWindow = window;
    mInputQueue = inputQueue;

    luabridge::setGlobal(LuaManager::getManager()->getState(), &mActionManager,
                         "GPurityActionManager");
}

void Purity::InputSystem::update(Scene* scene)
{
    if (mCurrentScene != scene)
    {
        mCurrentScene = scene;
    }

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
#ifdef __ANDROID__
            else if (event.keyEvent.code == SDLK_AC_BACK)
            {
                if (!mWindow->isContentMode())
                {
                    mWindow->close();
                }
            }
            else if (event.keyEvent.code == SDLK_MENU)
            {
                mWindow->toggleMode();
            }
#endif
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
        else if (!mWindow->isContentMode())
        {
            mActionManager.disableAll();
        }
    }
}
