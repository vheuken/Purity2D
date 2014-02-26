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
    doDrag = false;
    dragX = 0;
    dragY = 0;
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
        else if (isWindowManipulationEvent(event))
        {
            manipulateWindow(event);
        }
    }
}

bool Purity::InputManager::isWindowManipulationEvent(const sf::Event& event) const
{
    if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased || event.type == sf::Event::MouseMoved)
    {
        return true;
    }

    return false;
}

void Purity::InputManager::manipulateWindow(const sf::Event& event)
{
    setWindowFlags(event);

    if (mWindowDrag)
    {
        dragWindow();
    }
    else if (mWindowResize)
    {
        resizeWindow();
    }
}

void Purity::InputManager::setWindowFlags(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (isMouseOnBorder())
            {
                mWindowResize = true;
                std::cout << "Border grabbed!" << std::endl;
            }
            else
            {
                mWindowDrag = true;
                std::cout << "Window grabbed!" << std::endl;

                dragX = sf::Mouse::getPosition(*mWindow).x;
                dragY = sf::Mouse::getPosition(*mWindow).y;
                mLastMousePosRelativeToWindow = sf::Mouse::getPosition(*mWindow);

            }
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (mWindowResize)
            {
                mWindowResize = false;
                std::cout << "Border released!" << std::endl;
            }
            else if (mWindowDrag == false)
            {
                mWindowDrag = false;
                std::cout << "Window released!" << std::endl;
            }
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false && mWindowDrag == true)
    {
        mWindowDrag = false;
        std::cout << "Window released!" << std::endl;
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
