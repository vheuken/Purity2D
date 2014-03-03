#include "physicssystem.h"

#include <string>
#include <luabind/luabind.hpp>
#include "luamanager.h"
#include "../framework/scene.h"

Purity::PhysicsSystem::PhysicsSystem(std::queue<SDL_Event>* inputQueue, std::queue<NetworkAction>* serverActionQueue)
{
    mWorld = std::unique_ptr<b2World>(new b2World(GRAVITY));

    mCurrentScene = nullptr;
    mLastTime = 0;
    mFrameTimeMilleseconds = 0;
    mFrameTimer.restart().asMicroseconds();

    mInputQueue = inputQueue;
    mServerActionQueue = serverActionQueue;
}

void Purity::PhysicsSystem::update(Purity::Scene* scene)
{
/*
    if (scene != mCurrentScene)
    {
        LuaManager* luaManager = LuaManager::getManager();

        mCurrentScene = scene;

        mCurrentScene->initializePhysics(mWorld.get());

        std::string luaEventHandlerFileName = mCurrentScene->getLuaEventHandlerPath();
        std::string luaEventHandlerFunction = mCurrentScene->getLuaEventHandlerFunctionName();

        luaManager->doFile(luaEventHandlerFileName);

        std::string physicsUpdateScript = mCurrentScene->getLuaPhysicsUpdatePath();

        luaManager->doFile(physicsUpdateScript);

        // NETWORK STUFF
        luaManager->doFile("scenes/init/serverActionHandler.lua");
    }

    step();
    mCurrentScene->updatePhysics();
    */
}

void Purity::PhysicsSystem::step()
{
    static float acumulator = 0.0;

    mLastTime = mFrameTimeMilleseconds;
    mFrameTimeMilleseconds = mFrameTimer.getElapsedTime().asMilliseconds();

    acumulator += (mFrameTimeMilleseconds - mLastTime);

    while (acumulator >= (TIME_STEP * 1000))
    {
	    handleInput();
        handleServerActions();
		runUpdateScripts();

        mWorld->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

        acumulator -= (TIME_STEP * 1000);
    }
}

void Purity::PhysicsSystem::handleInput()
{
    std::string luaEventHandlerFileName = mCurrentScene->getLuaEventHandlerPath();
    std::string luaEventHandlerFunction = mCurrentScene->getLuaEventHandlerFunctionName();
    LuaManager* luaManager = LuaManager::getManager();
    lua_State* luaState = luaManager->getState();

    while (!mInputQueue->empty())
    {
	    SDL_Event event = mInputQueue->front();
	    mInputQueue->pop();

	    luabind::call_function<void>(luaState, luaEventHandlerFunction.c_str(), event);
    }
}

void Purity::PhysicsSystem::handleServerActions()
{
    LuaManager* luaManager = LuaManager::getManager();
    while (!mServerActionQueue->empty())
    {
        NetworkAction action = mServerActionQueue->front();
        mServerActionQueue->pop();

        luabind::call_function<void>(luaManager->getState(), "serverActionHandler", action.objectName, action.actionName);
    }
}

void Purity::PhysicsSystem::runUpdateScripts()
{
    LuaManager* luaManager = LuaManager::getManager();

    luabind::call_function<void>(luaManager->getState(), "onPhysicsUpdate");
}
