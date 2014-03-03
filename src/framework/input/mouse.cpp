#include "mouse.h"

#ifdef __gnu_linux__
#include <X11/Xlib.h>
#elif defined _WIN32
#include <windows.h>
#endif

#include <SFML/Window/Mouse.hpp>

Purity::Vector2i Purity::Mouse::getPosition()
{
#ifdef __gnu_linux__
    // Open a connection with the X server
    Display* display = XOpenDisplay(NULL);

    // we don't care about these but they are required
    ::Window root, child;
    int x, y;
    unsigned int buttons;

    int gx = 0;
    int gy = 0;
    XQueryPointer(display, DefaultRootWindow(display), &root, &child, &gx, &gy, &x, &y, &buttons);

    // Close the connection with the X server
    XCloseDisplay(display);

    return Vector2i(gx, gy);
#elif defined _WIN32
    POINT point;
    GetCursorPos(&point);
    return Vector2i(point.x, point.y);
#endif
}


Purity::Vector2i Purity::Mouse::getPosition(const Purity::Window& relativeTo)
{
    sf::Vector2i pos = sf::Mouse::getPosition(relativeTo.getInternalWindow());

    return Vector2i(pos.x, pos.y);
}

bool Purity::Mouse::isButtonPressed(Button button)
{
    switch(button)
    {
    case Left:
        return sf::Mouse::isButtonPressed(sf::Mouse::Left);

    case Right:
        return sf::Mouse::isButtonPressed(sf::Mouse::Right);
    case Middle:
        return sf::Mouse::isButtonPressed(sf::Mouse::Middle);
    }

    return false;
}
