#include "engine.h"

#include <iostream>
#include <luabind/luabind.hpp>
#include "luamanager.h"

#ifdef __gnu_linux__
#include <X11/Xlib.h>
#endif

void Purity::Engine::initialize()
{
    std::cout << "Initializing some stuff..." << std::endl;

    #ifdef __gnu_linux__
    XInitThreads();
    #endif
   
    mInputQueue = std::unique_ptr<std::queue<sf::Event> >(new std::queue<sf::Event>);		
    mServerActionQueue = std::unique_ptr<std::queue<NetworkAction> >(new std::queue<NetworkAction>);
    initializeWindow();
    initializeRenderer();
    initializeSceneManager();
    initializePhysicsSystem();
    initializeInputManager();
    initializeNetworkManager();

    luabind::globals(LuaManager::getManager()->getState())["GPurityEngine"] = this;
}

void Purity::Engine::run()
{
    std::cout << "Engine is starting! =D" << std::endl;
    Scene* currentScene = nullptr;

    while (mWindow->isOpen())
    {
        if (currentScene != mSceneManager->getCurrentScene())
        {
            currentScene = mSceneManager->getCurrentScene();
        }
        
        mNetworkManager->update();
        mInputManager->update();
        mPhysicsSystem->update(currentScene);
        mRenderer->update(currentScene);
    }

    // solves crash on exit on Windows
    mRenderer->update(nullptr);
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

void Purity::Engine::initializeRenderer()
{
    mRenderer = std::unique_ptr<Renderer>(new Renderer(mWindow.get()));
}

void Purity::Engine::initializeSceneManager()
{
    mSceneManager = std::unique_ptr<SceneManager>(new SceneManager());
}

void Purity::Engine::initializePhysicsSystem()
{
    mPhysicsSystem = std::unique_ptr<PhysicsSystem>(new PhysicsSystem(mInputQueue.get()));
}

void Purity::Engine::initializeInputManager()
{
    mInputManager = std::unique_ptr<InputManager>(new InputManager(mWindow.get(), mInputQueue.get()));
}

void Purity::Engine::initializeNetworkManager()
{
    mNetworkManager = std::unique_ptr<NetworkManager>(new NetworkManager(mServerActionQueue.get()));
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