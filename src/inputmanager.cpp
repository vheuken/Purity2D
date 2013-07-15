#include "inputmanager.h"

Purity::InputManager::InputManager(sf::RenderWindow* window)
{
    mWindow = window;
    mCurrentScene = nullptr;
}

void Purity::InputManager::update(Scene* scene)
{
    if (mCurrentScene != scene)
    {
        mCurrentScene = scene;
    }

    sf::Event event;
    std::string luaEventHandlerFile = mCurrentScene->getLuaEventHandlerPath();
    std::string luaEventHandlerFunction = mCurrentScene->getLuaEventHandlerFunctionName();
    lua_State* luaState = LuaManager::getManager()->getState();

    while (mWindow->pollEvent(event))
    {
        luaL_dofile(luaState, luaEventHandlerFile.c_str());
        luabind::call_function<void>(luaState, luaEventHandlerFunction.c_str(), event);

        if (event.type == sf::Event::Closed)
        {
            mWindow->close();
        }
    }
}