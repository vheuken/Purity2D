#include "rect.h"

Purity::Rect::Rect()
{
}

Purity::Rect::Rect(Vector2i p, int w, int h)
    : position(p)
    , width(w)
    , height(h)
{
}

Purity::Rect::operator SDL_Rect() const
{
    SDL_Rect rect;

    rect.x = position.x;
    rect.y = position.y;

    rect.h = height;
    rect.w = width;

    return rect;
}
