#include "inputmanager.h"

#include <iostream>
#include <queue>

#include "../framework/window/window.h"
#include "../framework/input/mouse.h"
#include <SDL_events.h>

Purity::InputManager::InputManager(Purity::Window* window, std::queue<SDL_Event>* inputQueue)
{
    mWindow = window;
    mInputQueue = inputQueue;
}

void Purity::InputManager::update()
{
    SDL_Event event;

    while (mWindow->pollEvent(&event))
    {
        mInputQueue->push(event);

        if (event.type == SDL_WINDOWEVENT)
        {
            if (event.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                mWindow->close();
            }
        }
        else if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                mWindow->close();
            }
        }
    }

    mWindow->manipulateWindow();
}
