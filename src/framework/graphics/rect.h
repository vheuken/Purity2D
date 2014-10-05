#ifndef PURITY_RECT_H
#define PURITY_RECT_H

#include <SDL.h>

#include "../system/vector2.h"

namespace Purity
{
    class Rect
    {
    public:
        Rect();
        Rect(Vector2i p, int w, int h);

        Vector2i position;

        int width;
        int height;

        explicit operator SDL_Rect() const;
    };
}

#endif // PURITY_RECT_H
