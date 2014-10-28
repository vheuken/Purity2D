#ifndef PURITY_MOUSE_H
#define PURITY_MOUSE_H

#include <SDL.h>

#include "../system/vector2.h"

namespace Purity
{
class Window;

class Mouse
{
public:
    enum MouseButton
    {
        Left = SDL_BUTTON_LEFT,
        Middle = SDL_BUTTON_MIDDLE,
        Right = SDL_BUTTON_RIGHT,
        XButton1 = SDL_BUTTON_X1,
        XButton2 = SDL_BUTTON_X2
    };

    static Vector2i getPosition();
    static Vector2i getPosition(const Window& relativeTo);
    static bool isButtonPressed(MouseButton button);
};
}

#endif // PURITY_MOUSE_H
