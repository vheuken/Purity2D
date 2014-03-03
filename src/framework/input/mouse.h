#ifndef PURITY_MOUSE_H
#define PURITY_MOUSE_H

#include "../system/vector2.h"
#include "../window/window.h"

namespace Purity
{
    class Mouse
    {
    public:
        enum Button
        {
            Left,
            Right,
            Middle,

            ButtonCount
        };

        static Vector2i getPosition();
        static Vector2i getPosition(const Window& relativeTo);
        static bool isButtonPressed(Button button);
    };
}

#endif // PURITY_MOUSE_H
