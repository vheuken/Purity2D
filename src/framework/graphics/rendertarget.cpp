#include "rendertarget.h"

#include <iostream>
#include <SDL.h>
#include "drawable.h"

void Purity::RenderTarget::clear()
{
    if (SDL_SetRenderDrawColor(sRenderer, 0, 0, 0, 255) < 0)
    {
        std::cout << SDL_GetError() << std::endl;
    }

    if(SDL_RenderClear(sRenderer)  < 0)
    {
        std::cout << SDL_GetError() << std::endl;
    }
}

void Purity::RenderTarget::display()
{
    SDL_RenderPresent(sRenderer);
}

void Purity::RenderTarget::draw(const Drawable& drawable)
{
    drawable.draw(*this);
}

void Purity::RenderTarget::draw(const Purity::VertexArray& vertexArray, const Purity::Vector2f& position)
{
    if (vertexArray.getVertexCount() == 4)
    {
        SDL_Rect rect = static_cast<SDL_Rect>( vertexArray.getBounds() );

        rect.x = position.x;
        rect.y = position.y;

        if (SDL_SetRenderDrawColor(sRenderer, 255, 0, 0, 255) < 0)
        {
            std::cout << SDL_GetError() << std::endl;
        }

        if (SDL_RenderDrawRect(sRenderer, &rect) < 0)
        {
            std::cout << SDL_GetError() << std::endl;
        }
    }
}
