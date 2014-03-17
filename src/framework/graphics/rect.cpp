#include "rect.h"

Purity::Rect::operator SDL_Rect()
{
    SDL_Rect rect;

    rect.x = position.x;
    rect.y = position.y;

    rect.h = height;
    rect.w = width;
}
