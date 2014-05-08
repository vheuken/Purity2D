// TODO: Lua stuff

#include "physicssystem.h"

#include <string>
#include <lua.hpp>
#include <LuaBridge.h>
#include "luamanager.h"
#include "../framework/scene.h"

Purity::PhysicsSystem::PhysicsSystem(std::queue<SDL_Event>* inputQueue, std::queue<NetworkAction>* serverActionQueue)
{
    mWorld = std::unique_ptr<b2World>(new b2World(GRAVITY));

    mCurrentScene = nullptr;
    mLastTime = 0;
    mFrameTimeMilleseconds = 0;
    //mFrameTimer.restart().asMicroseconds();

    mInputQueue = inputQueue;
    mServerActionQueue = serverActionQueue;
}

void Purity::PhysicsSystem::update(Purity::Scene* scene)
{
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
        //luaManager->doFile("scenes/init/serverActionHandler.lua");
    }

    step();
    mCurrentScene->updatePhysics();
}

void Purity::PhysicsSystem::step()
{
    static float acumulator = 0.0;

    mLastTime = mFrameTimeMilleseconds;
    mFrameTimeMilleseconds = mFrameTimer.getElapsedTime();

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

    while (!mInputQueue->empty())
    {
	    SDL_Event event = mInputQueue->front();
	    mInputQueue->pop();

//	    luabind::call_function<void>(luaState, luaEventHandlerFunction.c_str(), event);
        try{
        luabridge::LuaRef update = luabridge::getGlobal(luaManager->getState(), luaEventHandlerFunction.c_str());
        update(event);
        } catch (luabridge::LuaException e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}

void Purity::PhysicsSystem::handleServerActions()
{
    LuaManager* luaManager = LuaManager::getManager();
    while (!mServerActionQueue->empty())
    {
        NetworkAction action = mServerActionQueue->front();
        mServerActionQueue->pop();

        luabridge::LuaRef update = luabridge::getGlobal(luaManager->getState(), "serverActionHandler");
        update(action.objectName, action.actionName);
    }
}

void Purity::PhysicsSystem::runUpdateScripts()
{
    LuaManager* luaManager = LuaManager::getManager();

    luabridge::LuaRef update = luabridge::getGlobal(luaManager->getState(), "onPhysicsUpdate");
    update();
}
