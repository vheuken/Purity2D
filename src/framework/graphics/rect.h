#ifndef PURITY_RECT_H
#define PURITY_RECT_H

#include <SDL.h>

#include "../system/vector2.h"

namespace Purity
{
    class Rect
    {
    public:
        Vector2i position;

        int height;
        int width;

        explicit operator SDL_Rect() const;
    };
}

#endif // PURITY_RECT_H
