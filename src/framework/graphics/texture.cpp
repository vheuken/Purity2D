#include "texture.h"

#include <iostream>
#include <SDL.h>

bool Purity::Texture::loadFromFile(const std::string& path)
{
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());

    if (surface == nullptr)
    {
        std::cerr << SDL_GetError() << std::endl;
        return false;
    }

    mInternalTexture = SDL_CreateTextureFromSurface(sRenderer, surface);

    SDL_FreeSurface(surface);

    if (mInternalTexture == nullptr)
    {
        std::cerr << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

Purity::Vector2u Purity::Texture::getSize() const
{
    int width, height;

    SDL_QueryTexture(mInternalTexture, NULL, NULL, &width, &height);

    return Vector2u(static_cast<unsigned int>(width),
                    static_cast<unsigned int>(height));
}

Purity::Texture::~Texture()
{
    SDL_DestroyTexture(mInternalTexture);
}
