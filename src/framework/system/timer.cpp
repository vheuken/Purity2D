#include "timer.h"

#include <SDL.h>

#include <lua.hpp>

#include <LuaBridge.h>

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

void Purity::Timer::luaBindings(lua_State* state)
{
    luabridge::getGlobalNamespace(state)
        .beginNamespace("Purity")
        .beginClass<Timer>("Timer")
        .addConstructor<void (*)(void)>()
        .addFunction("getElapsedTime", &Timer::getElapsedTime)
        .addFunction("restart", &Timer::restart)
        .endClass()
        .endNamespace();
}
