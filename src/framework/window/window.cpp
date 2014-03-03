#include "window.h"
#include <iostream>

#include <SFML/System/Vector2.hpp>

// HACK
// sf::Style::None won't work on Linux....
Purity::Window::Window(int width, int height, std::string title)
:
#ifdef __gnu_linux__
mInternalWindow(sf::VideoMode(width, height), title, 0),
#else
mWindow = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(videoMode, "Purity2D", sf::Style::None)),
#endif
mWindowManipulator(this)
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

void Purity::Window::setSize(const Vector2u& size)
{
    sf::Vector2u s(size.x, size.y);
    mInternalWindow.setSize(s);
}

Purity::Vector2u Purity::Window::getSize() const
{
    return Vector2u(mInternalWindow.getSize().x, mInternalWindow.getSize().y);
}

void Purity::Window::setPosition(const Vector2i& position)
{
    sf::Vector2i p(position.x, position.y);
    mInternalWindow.setPosition(p);
}

Purity::Vector2i Purity::Window::getPosition() const
{
    return Vector2i(mInternalWindow.getPosition().x, mInternalWindow.getPosition().y);
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
    mWindowManipulator.manipulateWindow();
}

const sf::Window& Purity::Window::getInternalWindow() const
{
    return mInternalWindow;
}
