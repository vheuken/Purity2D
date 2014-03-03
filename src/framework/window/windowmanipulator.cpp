#include "windowmanipulator.h"

#include "window.h"
#include "../input/mouse.h"

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
    if (Mouse::isButtonPressed(Mouse::Left))
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

            mLastMousePosRelativeToWindow = Mouse::getPosition(*mWindow);
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
    Vector2u windowSize = mWindow->getSize();
    Vector2u newWindowSize = windowSize;
    Vector2i newWindowPos = mWindow->getPosition();

    Vector2u mousePos;

    mousePos.x = (unsigned int)Mouse::getPosition(*mWindow).x;
    mousePos.y = (unsigned int)Mouse::getPosition(*mWindow).y;

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
    mWindow->setPosition(Mouse::getPosition() - mLastMousePosRelativeToWindow);
}

void Purity::WindowManipulator::resizeWindow()
{
    Vector2u windowSize = mWindow->getSize();
    Vector2u newWindowSize = windowSize;
    Vector2i newWindowPos = mWindow->getPosition();

    Vector2u mousePos;

    mousePos.x = (unsigned int)Mouse::getPosition().x;
    mousePos.y = (unsigned int)Mouse::getPosition().y;

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
    Vector2i mousePositionRelativeToWindow = Mouse::getPosition(*mWindow);
    Vector2u windowSize = mWindow->getSize();

    if ((mousePositionRelativeToWindow.x >= windowSize.x - STRETCHABLE_BORDER_PIXELS && mousePositionRelativeToWindow.x <= windowSize.x) ||
        (mousePositionRelativeToWindow.y >= windowSize.y - STRETCHABLE_BORDER_PIXELS && mousePositionRelativeToWindow.y <= windowSize.y) ||
        mousePositionRelativeToWindow.x <= STRETCHABLE_BORDER_PIXELS ||
        mousePositionRelativeToWindow.y <= STRETCHABLE_BORDER_PIXELS)
    {
        return true;
    }

    return false;
}
