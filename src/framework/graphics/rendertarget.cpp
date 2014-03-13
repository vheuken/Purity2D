#include "rendertarget.h"

#include <iostream>
#include <SDL.h>
#include "drawable.h"

void Purity::RenderTarget::clear()
{
    SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);

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

void Purity::RenderTarget::draw(const Purity::VertexArray& vertexArray, const Purity::Vector2f& position)
{;
    if (vertexArray.getVertexCount() == 4)
    {
        //std::cout << "H" <<std::endl;
        SDL_Rect rect;

        rect.x = position.x;
        rect.y = position.y;

        rect.w = vertexArray[1].position.x - vertexArray[0].position.x;
        rect.h = vertexArray[2].position.y - vertexArray[0].position.y;

        if (SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255) < 0)
        {
            std::cout << SDL_GetError() << std::endl;
        }

        if (SDL_RenderDrawRect(mRenderer, &rect) < 0)
        {
            std::cout << SDL_GetError() << std::endl;
        }

        SDL_RenderPresent(mRenderer);
    }
}
