#include "engine.h"

#include <iostream>
#include "luamanager.h"
#include "../framework/graphics/texturemanager.h"

Purity::Engine::Engine(const CommandLineArguments& commandLineArguments)
    : mProgramOptions(commandLineArguments)
{
    std::cout << "Initializing some stuff..." << std::endl;

    mInputQueue = std::unique_ptr<std::queue<Event> >(new std::queue<Event>);
    mServerActionQueue = std::unique_ptr<std::queue<NetworkAction> >(new std::queue<NetworkAction>);

    if (mProgramOptions.headless == false)
    {
        initializeWindow();
        initializeRenderSystem();
        initializeInputManager();
    }
    else
    {
        TextureManager::sIsEnabled = false;
    }

    initializeSceneManager();
    initializePhysicsSystem();
    initializeNetworkSystem();
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
            mInputManager->update();
            mWindow->manipulateWindow();
        }
    }
}

void Purity::Engine::initializeWindow()
{
    mWindow = std::unique_ptr<Purity::Window>(new Purity::Window(960, 720, "Purity2D"));
}

void Purity::Engine::initializeRenderSystem()
{
    mRenderSystem = std::unique_ptr<RenderSystem>(new RenderSystem(mWindow.get()));
}

void Purity::Engine::initializeSceneManager()
{
    mSceneManager = std::unique_ptr<SceneManager>(new SceneManager());
}

void Purity::Engine::initializePhysicsSystem()
{
    mPhysicsSystem = std::unique_ptr<PhysicsSystem>(new PhysicsSystem(mInputQueue.get(), mServerActionQueue.get()));
}

void Purity::Engine::initializeInputManager()
{
    mInputManager = std::unique_ptr<InputManager>(new InputManager(mWindow.get(), mInputQueue.get()));
}

void Purity::Engine::initializeNetworkSystem()
{
    mNetworkSystem = std::unique_ptr<NetworkSystem>(new NetworkSystem(mServerActionQueue.get()));
}
