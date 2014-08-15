#ifndef PURITY_EVENT_H
#define PURITY_EVENT_H

#include <SDL.h>

namespace Purity
{
    enum EventType
    {
        KeyPressed             = SDL_KEYDOWN,          // TODO: Implement
        KeyReleased            = SDL_KEYUP,            // TODO: Implement

        MouseMoved             = SDL_MOUSEMOTION,      // TODO: Implement
        MouseWheelMoved        = SDL_MOUSEWHEEL,       // TODO: Implement
        MouseButtonPressed     = SDL_MOUSEBUTTONDOWN,  // TODO: Implement
        MouseButtonReleased    = SDL_MOUSEBUTTONUP,    // TODO: Implement

        JoystickButtonPressed  = SDL_JOYBUTTONDOWN,    // TODO: Implement
        JoystickButtonReleased = SDL_JOYBUTTONUP,      // TODO: Implement
        JoystickMoved          = SDL_JOYAXISMOTION,    // TODO: Implement
        JoystickConnected      = SDL_JOYDEVICEADDED,   // TODO: Implement
        JoystickDisconnected   = SDL_JOYDEVICEREMOVED, // TODO: Implement

        TouchBegan             = SDL_FINGERDOWN,       // TODO: Implement
        TouchMoved             = SDL_FINGERMOTION,     // TODO: Implement
        TouchEnded             = SDL_FINGERUP          // TODO: Implement
    };

    class Event
    {
    public:
        EventType getType() const;
    private:
        SDL_Event mEvent;
    };
}

#endif // PURITY_EVENT_H
