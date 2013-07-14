#include "engine.h"

void Purity::Engine::initialize()
{
    std::cout << "Initializing some stuff..." << std::endl;

    initializeWindow();
    initializeRenderer();
    initializeSceneManager();
    initializePhysicsSystem();
    initializeInputManager();
}

void Purity::Engine::run()
{
    std::cout << "Engine is starting! =D" << std::endl;
    Scene* currentScene;

    while (mWindow->isOpen())
    {
        currentScene = mSceneManager->getCurrentScene();

        mRenderer->update(currentScene);
        mPhysicsSystem->update(currentScene);
        mInputManager->update(currentScene);
    }

}

void Purity::Engine::cleanup()
{
    std::cout << "Cleaning up..." << std::endl;
}

void Purity::Engine::initializeWindow()
{
    sf::VideoMode videoMode(800, 600);

    mWindow = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(videoMode, "Purity2D"));
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
    mPhysicsSystem = std::unique_ptr<PhysicsSystem>(new PhysicsSystem());
}

void Purity::Engine::initializeInputManager()
{
    mInputManager = std::unique_ptr<InputManager>(new InputManager(mWindow.get()));
}