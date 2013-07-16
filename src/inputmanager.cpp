#include "inputmanager.h"

Purity::InputManager::InputManager(sf::RenderWindow* window, std::queue<sf::Event>* inputQueue)
{
    mWindow = window;
    mCurrentScene = nullptr;
    mInputQueue = inputQueue;
}

void Purity::InputManager::update(Scene* scene)
{
    if (mCurrentScene != scene)
    {
        mCurrentScene = scene;
    }

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
