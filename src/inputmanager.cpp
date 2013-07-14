#include "inputmanager.h"

Purity::InputManager::InputManager(sf::RenderWindow* window)
{
    mWindow = window;
}

void Purity::InputManager::update(Scene* scene)
{
    sf::Event event;
    lua_State* luaState = LuaManager::getManager()->getState();

    while (mWindow->pollEvent(event))
    {
        luaL_dofile(luaState, "eventHandler.lua");
        luabind::call_function<void>(luaState, "eventHandler", event);
        if (event.type == sf::Event::Closed)
        {
            mWindow->close();
        }
    }
}