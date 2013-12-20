#include "inputmanager.h"

#include <queue>
#include <SFML/Graphics.hpp>

Purity::InputManager::InputManager(sf::RenderWindow* window, std::queue<sf::Event>* inputQueue)
{
    mWindow = window;
    mInputQueue = inputQueue;
}

void Purity::InputManager::update()
{
    sf::Event event;

    while (mWindow->pollEvent(event))
    {
	    mInputQueue->push(event);
        if (event.type == sf::Event::Closed)
        {
            mWindow->close();
        }
    }
}
