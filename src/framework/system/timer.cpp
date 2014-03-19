#include "timer.h"

#include <SDL.h>

Purity::Timer::Timer()
{
    restart();
}

unsigned int Purity::Timer::getElapsedTime() const
{
    return SDL_GetTicks() - mStartingTick;
}

void Purity::Timer::restart()
{
    mStartingTick = SDL_GetTicks();
}
