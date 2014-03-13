#include "rendertarget.h"

#include <SDL.h>
#include "drawable.h"

Purity::RenderTarget::RenderTarget()
{
}

void Purity::RenderTarget::clear()
{
    SDL_RenderClear(mRenderer);
}

void Purity::RenderTarget::draw(const Drawable& drawable)
{
    drawable.draw(*this);
}

void Purity::RenderTarget::display()
{
    SDL_RenderPresent(mRenderer);
}
