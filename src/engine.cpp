#include "engine.h"

void Purity::Engine::initialize()
{
    std::cout << "Initializing some stuff..." << std::endl;
    mMap = std::unique_ptr<GameMap>(new GameMap("test.tmx"));
}

void Purity::Engine::run()
{
    std::cout << "Engine is starting! =D" << std::endl;
    sf::RenderWindow window(sf::VideoMode(800, 600), "bilyl'd my pants");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();
        window.draw(*mMap);
        window.display();
    }

}

void Purity::Engine::cleanup()
{

}