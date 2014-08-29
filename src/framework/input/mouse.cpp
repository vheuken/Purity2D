#include "mouse.h"

#ifdef __gnu_linux__
#include <X11/Xlib.h>
#elif defined _WIN32
#include <windows.h>
#elif __APPLE__ && !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
#include <ApplicationServices/ApplicationServices.h>
#endif

#include <SDL_events.h>

Purity::Vector2i Purity::Mouse::getPosition()
{
    Vector2i ret(0,0);
    
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

    ret.x = gx;
    ret.y = gy;
#elif defined _WIN32
    POINT point;
    GetCursorPos(&point);
    
    ret.x = point.x;
    ret.y = point.y;
#elif defined __APPLE__ && !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
    auto event = CGEventCreate(nullptr);
    auto cursor = CGEventGetLocation(event);
    
    ret.x = cursor.x;
    ret.y = cursor.y;
    
    CFRelease(event);
#endif
    
    return ret;
}


Purity::Vector2i Purity::Mouse::getPosition(const Purity::Window& relativeTo)
{
    int x, y;

    SDL_PumpEvents();
    SDL_GetMouseState(&x, &y);

    return Vector2i(x, y);
}

bool Purity::Mouse::isButtonPressed(Button button)
{
    SDL_PumpEvents();

    return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(button);
}
