#include "engine.h"

#include <iostream>
#include "luamanager.h"
#include "../framework/graphics/texturemanager.h"
#include <LuaBridge.h>

#ifdef _WIN32
#include "../framework/window/win32/window.h"
#endif

Purity::Engine::Engine(const CommandLineArguments& commandLineArguments)
    : mProgramOptions(commandLineArguments)
{
    std::cout << "Initializing some stuff..." << std::endl;

    mInputQueue = std::unique_ptr<std::queue<Event>>(new std::queue<Event>);
    mServerActionQueue = std::unique_ptr<std::queue<NetworkAction>>(
        new std::queue<NetworkAction>);

    if (mProgramOptions.headless == false)
    {
        initializeWindow();
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
        SDL_StartTextInput();
#endif
        initializeRenderSystem();
        initializeInputManager();
    }
    else
    {
        TextureManager::sIsEnabled = false;
    }

    initializePhysicsSystem();
    initializeNetworkSystem();
    initializeSceneManager();

    // TODO: move somewhere else?
    luabridge::setGlobal(LuaManager::getManager()->getState(),
                         LuaManager::getManager(), "GPurityLuaManager");
    luabridge::setGlobal(LuaManager::getManager()->getState(),
                         mSceneManager.get(), "GPuritySceneManager");
    luabridge::setGlobal(LuaManager::getManager()->getState(),
                         mWindow.get(), "GPurityWindow");
}

void Purity::Engine::run()
{
    std::cout << "Engine is starting! =D" << std::endl;
    Scene* currentScene = nullptr;

    while (mProgramOptions.headless || mWindow->isOpen())
    {
        if (currentScene != mSceneManager->getCurrentScene())
        {
            currentScene = mSceneManager->getCurrentScene();
        }

        mNetworkSystem->update(currentScene);
        mPhysicsSystem->update(currentScene);

        if (mProgramOptions.headless == false)
        {
            mRenderSystem->update(currentScene);
            mInputSystem->update(currentScene);
            mWindow->manipulateWindow();
        }
    }
}

void Purity::Engine::initializeWindow()
{
    Vector2i windowSize(Configuration::getInstance()->getInteger(
                            "window", "window_size_x", 800),
                        Configuration::getInstance()->getInteger(
                            "window", "window_size_y", 400));

#ifdef _WIN32
    mWindow = std::unique_ptr<Purity::Window>(
        new Purity::Win32Window(windowSize.x, windowSize.y, "Purity2D"));
#else
    mWindow = std::unique_ptr<Purity::Window>(
        new Purity::Window(windowSize.x, windowSize.y, "Purity2D"));
#endif
}

void Purity::Engine::initializeRenderSystem()
{
    mRenderSystem
        = std::unique_ptr<RenderSystem>(new RenderSystem(mWindow.get()));
}

void Purity::Engine::initializeSceneManager()
{
    mSceneManager = std::unique_ptr<SceneManager>(new SceneManager(mPhysicsSystem->getWorld()));
}

void Purity::Engine::initializePhysicsSystem()
{
    mPhysicsSystem = std::unique_ptr<PhysicsSystem>(
        new PhysicsSystem(mInputQueue.get(), mServerActionQueue.get()));
}

void Purity::Engine::initializeInputManager()
{
    mInputSystem = std::unique_ptr<InputSystem>(
        new InputSystem(mWindow.get(), mInputQueue.get()));
}

void Purity::Engine::initializeNetworkSystem()
{
    mNetworkSystem = std::unique_ptr<NetworkSystem>(
        new NetworkSystem(mServerActionQueue.get()));
}
