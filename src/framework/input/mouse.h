#ifndef PURITY_MOUSE_H
#define PURITY_MOUSE_H

#include <SDL_mouse.h>

#include "../system/vector2.h"
#include "../window/window.h"

namespace Purity
{
    class Mouse
    {
    public:
        enum Button
        {
            Left = SDL_BUTTON_LEFT,
            Right = SDL_BUTTON_RIGHT,
            Middle = SDL_BUTTON_MIDDLE
        };

        static Vector2i getPosition();
        static Vector2i getPosition(const Window& relativeTo);
        static bool isButtonPressed(Button button);
    };
}

#endif // PURITY_MOUSE_H
