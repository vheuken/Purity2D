#include "engine.h"

#include <iostream>
#include <luabind/luabind.hpp>
#include "luamanager.h"
#include "../framework/texturemanager.h"

#ifdef __gnu_linux__
#include <X11/Xlib.h>
#endif

Purity::Engine::Engine(const CommandLineArguments& commandLineArguments)
    : mProgramOptions(commandLineArguments)
{
}

void Purity::Engine::initialize()
{
    std::cout << "Initializing some stuff..." << std::endl;

    #ifdef __gnu_linux__
    XInitThreads();
    #endif
   
    mInputQueue = std::unique_ptr<std::queue<sf::Event> >(new std::queue<sf::Event>);		
    mServerActionQueue = std::unique_ptr<std::queue<NetworkAction> >(new std::queue<NetworkAction>);
    mReceivedStates = std::unique_ptr<std::map<unsigned int, EntityState>>(new std::map<unsigned int, EntityState>);
    
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

    luabind::globals(LuaManager::getManager()->getState())["GPurityEngine"] = this;
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
            mInputManager->update();
            mRenderSystem->update(currentScene);
        }
    }

    // solves crash on exit on Windows
    if (mProgramOptions.headless == false)
    {
        mRenderSystem->update(nullptr);
    }
}

void Purity::Engine::cleanup()
{
    std::cout << "Cleaning up..." << std::endl;
}

void Purity::Engine::initializeWindow()
{
    sf::VideoMode videoMode(960, 720);

    mWindow = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(videoMode, "Purity2D"));

    mWindow->setActive(false);
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
    mNetworkSystem = std::unique_ptr<NetworkSystem>(new NetworkSystem(mServerActionQueue.get(),
                                                                      mReceivedStates.get()));
}

sf::View Purity::Engine::getView()
{
    return mWindow->getView();
}

void Purity::Engine::setView(const sf::View & view)
{
    mWindow->setView(view);
}

luabind::scope Purity::Engine::luaBindings()
{
    return luabind::class_<Engine>("Engine")
        .def("getView", &Engine::getView)
        .def("setView", &Engine::setView)
    ;
}
