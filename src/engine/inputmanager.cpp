#include "inputmanager.h"

#include <queue>
#include <SFML/Graphics.hpp>

#if !_WIN32
#include <X11/Xlib.h>
#endif

Purity::InputManager::InputManager(sf::RenderWindow* window, std::queue<sf::Event>* inputQueue)
{
    mWindow = window;
    mInputQueue = inputQueue;

    // Window manipulation stuff to be refactored away
    mWindowDrag = false;
    mWindowResize = false;
    doDrag = false;
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
    if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased || event.type == sf::Event::MouseButtonReleased || event.type == sf::Event::MouseMoved)
    {
        return true;
    }

    return false;
}

#include <iostream>
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

    mLastMousePosRelativeToWindow = sf::Mouse::getPosition(*mWindow);
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
                

                // We don't use these variables, but they're required
                ::Window root, child;
                int f, b;
                unsigned int u;
                    
                Display* display = XOpenDisplay(NULL);
                XQueryPointer(display, DefaultRootWindow(display), &root, &child, &dragX, &dragY, &f, &b, &u);
                XCloseDisplay(display);
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
            else
            {
                mWindowDrag = false;
                std::cout << "Window released!" << std::endl;

            }
        }
    }
}

void Purity::InputManager::dragWindow()
{
    #if !_WIN32
    sf::WindowHandle handle = mWindow->getSystemHandle();
    Display* display = XOpenDisplay(NULL);
    
    // We don't use these variables, but they're required
    ::Window root, child;
    int f, b;
    unsigned int u;

    // get mouse coordinates
    int mousePosX, mousePosY;
    
    XQueryPointer(display, DefaultRootWindow(display), &root, &child, &mousePosX, &mousePosY, &f, &b, &u);
        
    
    // move window
    if (true)
    {
        XMoveWindow(display, handle, mWindow->getPosition().x + dragX - mousePosX, mWindow->getPosition().y + dragY - mousePosY); 
        
        std::cout << dragX - mousePosX << " " << dragY - mousePosY << std::endl;
        
        dragX = mousePosX;
        dragY = mousePosY;
    }
    XCloseDisplay(display);
    #else
    mWindow->setPosition(sf::Mouse::getPosition() - mLastMousePosRelativeToWindow);
    #endif
}

void Purity::InputManager::resizeWindow()
{
    sf::Vector2u newWindowSize = mWindow->getSize();

    
    mWindow->setSize(newWindowSize);
}

bool Purity::InputManager::isMouseOnBorder() const
{
    sf::Vector2i mousePositionRelativeToWindow = sf::Mouse::getPosition() - mWindow->getPosition();
    
    if (mousePositionRelativeToWindow.x >= mWindow->getSize().x - STRETCHABLE_BORDER_PIXELS ||
        mousePositionRelativeToWindow.y >= mWindow->getSize().y - STRETCHABLE_BORDER_PIXELS ||
        mousePositionRelativeToWindow.x <= STRETCHABLE_BORDER_PIXELS ||
        mousePositionRelativeToWindow.y <= STRETCHABLE_BORDER_PIXELS)
    {
        return true;
    }

    return false;
}
