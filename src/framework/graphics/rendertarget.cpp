#include "rendertarget.h"

#include <iostream>
#include <SDL.h>
#include "drawable.h"

void Purity::RenderTarget::clear()
{
    if (SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255) < 0)
    {
        std::cout << SDL_GetError() << std::endl;
    }

    if(SDL_RenderClear(mRenderer)  < 0)
    {
        std::cout << SDL_GetError() << std::endl;
    }
}

void Purity::RenderTarget::display()
{
    SDL_RenderPresent(mRenderer);
}

void Purity::RenderTarget::draw(const Drawable& drawable)
{
    drawable.draw(*this);
}

void Purity::RenderTarget::draw(const Purity::Rect& rectToDraw)
{
    SDL_Rect rect = static_cast<SDL_Rect>(rectToDraw);

    if (SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255) != 0)
    {
        std::cerr << SDL_GetError() << std::endl;
    }

    if (SDL_RenderDrawRect(mRenderer, &rect) != 0)
    {
        std::cerr << SDL_GetError() << std::endl;
    }
}

void Purity::RenderTarget::draw(const SpriteSheet* spriteSheet, unsigned short animationFrame, const Purity::Vector2f& position)
{
    auto texture = spriteSheet->getTexture();

    if (texture->mTextureCreationNeeded == true)
    {
        texture->createInternalTexture(mRenderer);
    }

    auto sdlTexture = static_cast<SDL_Texture*>(*texture);
    auto textureSubRect = static_cast<SDL_Rect>(spriteSheet->getTileSubRect(animationFrame));

    SDL_Rect drawRect;

    drawRect.x = position.x;
    drawRect.y = position.y;
    drawRect.w = textureSubRect.w;
    drawRect.h = textureSubRect.h;

    if (SDL_RenderCopy(mRenderer, sdlTexture, &textureSubRect, &drawRect) != 0)
    {
        std::cerr << SDL_GetError() << std::endl;
    }
}
