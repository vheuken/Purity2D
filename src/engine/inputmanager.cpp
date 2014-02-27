#include "inputmanager.h"

#include <iostream>
#include <queue>
#include <SFML/Graphics.hpp>

Purity::InputManager::InputManager(sf::RenderWindow* window, std::queue<sf::Event>* inputQueue)
{
    mWindow = window;
    mInputQueue = inputQueue;

    // Window manipulation stuff to be refactored away
    mWindowDrag = false;
    mWindowResize = false;
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

        manipulateWindow();
    }

}

void Purity::InputManager::manipulateWindow()
{
    setWindowFlags();

    if (mWindowDrag)
    {
        dragWindow();
    }
    else if (mWindowResize)
    {
        resizeWindow();
    }
}

void Purity::InputManager::setWindowFlags()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (mWindowResize == false && isMouseOnBorder())
        {
            mWindowResize = true;
            std::cout << "Border grabbed!" << std::endl;
        }
        else if (mWindowDrag == false)
        {
            mWindowDrag = true;
            std::cout << "Window grabbed!" << std::endl;

            mLastMousePosRelativeToWindow = sf::Mouse::getPosition(*mWindow);
        }
    }
    else
    {
        if (mWindowResize)
        {
            mWindowResize = false;
            std::cout << "Border released!" << std::endl;
        }
        else if (mWindowDrag)
        {
            mWindowDrag = false;
            std::cout << "Window released!" << std::endl;
        }
    }
}

void Purity::InputManager::dragWindow()
{
    mWindow->setPosition(sf::Mouse::getPosition() - mLastMousePosRelativeToWindow);
}

void Purity::InputManager::resizeWindow()
{
    sf::Vector2u newWindowSize = mWindow->getSize();


    mWindow->setSize(newWindowSize);
}

bool Purity::InputManager::isMouseOnBorder() const
{
    sf::Vector2i mousePositionRelativeToWindow = sf::Mouse::getPosition() - mWindow->getPosition();
    /*
    if (mousePositionRelativeToWindow.x >= mWindow->getSize().x - STRETCHABLE_BORDER_PIXELS ||
        mousePositionRelativeToWindow.y >= mWindow->getSize().y - STRETCHABLE_BORDER_PIXELS ||
        mousePositionRelativeToWindow.x <= STRETCHABLE_BORDER_PIXELS ||
        mousePositionRelativeToWindow.y <= STRETCHABLE_BORDER_PIXELS)
    {
        return true;
    }*/

    return false;
}
