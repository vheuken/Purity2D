// I essentially ganked this from SFML
// SFML is under the zlib license. You can check it out at: www.sfml-dev.org

#ifndef PURITY_EVENT_H
#define PURITY_EVENT_H

#include <SDL.h>

namespace Purity
{
    struct Event
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

        struct KeyEvent
        {
            SDL_Keycode code;
        };

        union
        {
            KeyEvent keyEvent;
        };

        EventType type;

        Event& operator=(const SDL_Event& event);
    };


    void convertKeyPressedEvent(Purity::Event& event, const SDL_Event& sdlEvent);
    void convertKeyReleasedEvent(Purity::Event& event, const SDL_Event& sdlEvent);
}

#endif // PURITY_EVENT_H
