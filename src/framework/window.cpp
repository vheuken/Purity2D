#include "window.h"
#include <iostream>

// HACK
// sf::Style::None won't work on Linux....
Purity::Window::Window(int width, int height, std::string title)
:
#ifdef __gnu_linux__
mInternalWindow(sf::VideoMode(width, height), title, 0),
#else
mWindow = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(videoMode, "Purity2D", sf::Style::None)),
#endif
mWindowDrag(false), mWindowResize(false),
mRightBorderGrabbed(false), mLeftBorderGrabbed(false), mBottomBorderGrabbed(false), mTopBorderGrabbed(false)
{
}

void Purity::Window::clear()
{
    mInternalWindow.clear();
}

void Purity::Window::draw(const sf::Drawable& drawable)
{
    mInternalWindow.draw(drawable);
}

void Purity::Window::display()
{
    mInternalWindow.display();
}

void Purity::Window::setView(const sf::View& view)
{
    mInternalWindow.setView(view);
}

const sf::View& Purity::Window::getView() const
{
    return mInternalWindow.getView();
}

bool Purity::Window::pollEvent(sf::Event& event)
{
    return mInternalWindow.pollEvent(event);
}

void Purity::Window::setActive(bool active)
{
    mInternalWindow.setActive(active);
}

bool Purity::Window::isOpen() const
{
    return mInternalWindow.isOpen();
}

void Purity::Window::close()
{
    mInternalWindow.close();
}

void Purity::Window::manipulateWindow()
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

void Purity::Window::setWindowFlags()
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

            mLastMousePosRelativeToWindow = sf::Mouse::getPosition(mInternalWindow);
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

void Purity::Window::setBorderGrabbedFlags()
{
    sf::Vector2u windowSize = mInternalWindow.getSize();
    sf::Vector2u newWindowSize = windowSize;
    sf::Vector2i newWindowPos = mInternalWindow.getPosition();

    sf::Vector2u mousePos;

    mousePos.x = (unsigned int)sf::Mouse::getPosition(mInternalWindow).x;
    mousePos.y = (unsigned int)sf::Mouse::getPosition(mInternalWindow).y;

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

void Purity::Window::dragWindow()
{
    mInternalWindow.setPosition(sf::Mouse::getPosition() - mLastMousePosRelativeToWindow);
}

void Purity::Window::resizeWindow()
{
    sf::Vector2u windowSize = mInternalWindow.getSize();
    sf::Vector2u newWindowSize = windowSize;
    sf::Vector2i newWindowPos = mInternalWindow.getPosition();

    sf::Vector2u mousePos;

    mousePos.x = (unsigned int)sf::Mouse::getPosition(mInternalWindow).x;
    mousePos.y = (unsigned int)sf::Mouse::getPosition(mInternalWindow).y;

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

    mInternalWindow.setPosition(newWindowPos);
    mInternalWindow.setSize(newWindowSize);
}

bool Purity::Window::isMouseOnBorder() const
{
    sf::Vector2i mousePositionRelativeToWindow = sf::Mouse::getPosition(mInternalWindow);
    sf::Vector2u windowSize = mInternalWindow.getSize();

    if ((mousePositionRelativeToWindow.x >= windowSize.x - STRETCHABLE_BORDER_PIXELS && mousePositionRelativeToWindow.x <= windowSize.x) ||
        (mousePositionRelativeToWindow.y >= windowSize.y - STRETCHABLE_BORDER_PIXELS && mousePositionRelativeToWindow.y <= windowSize.y) ||
        mousePositionRelativeToWindow.x <= STRETCHABLE_BORDER_PIXELS ||
        mousePositionRelativeToWindow.y <= STRETCHABLE_BORDER_PIXELS)
    {
        return true;
    }

    return false;
}
