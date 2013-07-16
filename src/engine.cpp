#include "engine.h"
#ifdef __gnu_linux__
#include <X11/Xlib.h>
#endif

void Purity::Engine::initialize(bool debugMode)
{
    std::cout << "Initializing some stuff..." << std::endl;

    #ifdef __gnu_linux__
    XInitThreads();
    #endif
   
    mDebugMode = debugMode;

    mInputQueue = std::unique_ptr<std::queue<sf::Event>>(new std::queue<sf::Event>);		
    
    initializeWindow();
    initializeRenderer();
    initializeSceneManager();
    initializePhysicsSystem();
    initializeInputManager();
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
            mRenderer->update(currentScene);
        }

        mPhysicsSystem->update(mSceneManager->getCurrentScene());
        mInputManager->update(mSceneManager->getCurrentScene());
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
    sf::VideoMode videoMode(800, 600);

    mWindow = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(videoMode, "Purity2D"));

    mWindow->setActive(false);
}

void Purity::Engine::initializeRenderer()
{
    mRenderer = std::unique_ptr<Renderer>(new Renderer(mWindow.get(), mDebugMode));
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
