#include "windowmanipulator.h"

#include "window.h"

#include <iostream>

Purity::WindowManipulator::WindowManipulator(Window* window)
: mWindow(window), mWindowDrag(false), mWindowResize(false),
mRightBorderGrabbed(false), mLeftBorderGrabbed(false), mBottomBorderGrabbed(false), mTopBorderGrabbed(false)
{
}

void Purity::WindowManipulator::manipulateWindow()
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

void Purity::WindowManipulator::setWindowFlags()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (mWindowResize == false && isMouseOnBorder())
        {
            mWindowResize = true;
            setBorderGrabbedFlags();
            std::cout << "Border grabbed!" << std::endl;
        }
        else if (mWindowDrag == false && mWindowResize == false)
        {
            mWindowDrag = true;
            std::cout << "Window grabbed!" << std::endl;

            mLastMousePosRelativeToWindow = sf::Mouse::getPosition(mWindow->getInternalWindow());
        }
    }
    else
    {
        if (mWindowResize)
        {
            mWindowResize = false;
            mRightBorderGrabbed = false;
            mLeftBorderGrabbed = false;
            mTopBorderGrabbed = false;
            mBottomBorderGrabbed = false;
            std::cout << "Border released!" << std::endl;
        }
        else if (mWindowDrag)
        {
            mWindowDrag = false;
            std::cout << "Window released!" << std::endl;
        }
    }
}

void Purity::WindowManipulator::setBorderGrabbedFlags()
{
    sf::Vector2u windowSize = mWindow->getSize();
    sf::Vector2u newWindowSize = windowSize;
    sf::Vector2i newWindowPos = mWindow->getPosition();

    sf::Vector2u mousePos;

    mousePos.x = (unsigned int)sf::Mouse::getPosition(mWindow->getInternalWindow()).x;
    mousePos.y = (unsigned int)sf::Mouse::getPosition(mWindow->getInternalWindow()).y;

    // right
    if (mousePos.x >= windowSize.x - STRETCHABLE_BORDER_PIXELS)
    {
        mRightBorderGrabbed = true;
    }

    // bottom
    if (mousePos.y >= windowSize.y - STRETCHABLE_BORDER_PIXELS)
    {
        mBottomBorderGrabbed = true;
    }
}

void Purity::WindowManipulator::dragWindow()
{
    mWindow->setPosition(sf::Mouse::getPosition() - mLastMousePosRelativeToWindow);
}

void Purity::WindowManipulator::resizeWindow()
{
    sf::Vector2u windowSize = mWindow->getSize();
    sf::Vector2u newWindowSize = windowSize;
    sf::Vector2i newWindowPos = mWindow->getPosition();

    sf::Vector2u mousePos;

    mousePos.x = (unsigned int)sf::Mouse::getPosition(mWindow->getInternalWindow()).x;
    mousePos.y = (unsigned int)sf::Mouse::getPosition(mWindow->getInternalWindow()).y;

    // right
    if (mRightBorderGrabbed)
    {
        newWindowSize.x = mousePos.x;
    }

    // bottom
    if (mBottomBorderGrabbed)
    {
        newWindowSize.y = mousePos.y;
    }

    // TODO: left

    // TODO: top

    mWindow->setPosition(newWindowPos);
    mWindow->setSize(newWindowSize);
}

bool Purity::WindowManipulator::isMouseOnBorder() const
{
    sf::Vector2i mousePositionRelativeToWindow = sf::Mouse::getPosition(mWindow->getInternalWindow());
    sf::Vector2u windowSize = mWindow->getSize();

    if ((mousePositionRelativeToWindow.x >= windowSize.x - STRETCHABLE_BORDER_PIXELS && mousePositionRelativeToWindow.x <= windowSize.x) ||
        (mousePositionRelativeToWindow.y >= windowSize.y - STRETCHABLE_BORDER_PIXELS && mousePositionRelativeToWindow.y <= windowSize.y) ||
        mousePositionRelativeToWindow.x <= STRETCHABLE_BORDER_PIXELS ||
        mousePositionRelativeToWindow.y <= STRETCHABLE_BORDER_PIXELS)
    {
        return true;
    }

    return false;
}
