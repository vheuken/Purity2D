#include "engine.h"

void Purity::Engine::initialize()
{
    std::cout << "Initializing some stuff..." << std::endl;
    mMap = std::unique_ptr<Scene>(new Scene("test_scene/"));

    initializeWindow();
    initializeRenderer();
}

void Purity::Engine::run()
{
    std::cout << "Engine is starting! =D" << std::endl;

    while (mWindow->isOpen())
    {
        sf::Event event;
        while (mWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                mWindow->close();
            }
        }
        
        mRenderer->update(*mMap);
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