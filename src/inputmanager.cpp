#include "inputmanager.h"

Purity::InputManager::InputManager(sf::RenderWindow* window)
{
    mWindow = window;
}

void Purity::InputManager::update(Scene* scene)
{
    sf::Event event;
    while (mWindow->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            mWindow->close();
        }
    }
}