#include "texture.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

bool Purity::Texture::loadFromFile(const std::string& path)
{
    SDL_Surface* surface = IMG_Load(path.c_str());

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

    if (SDL_QueryTexture(mInternalTexture, NULL, NULL, &width, &height) < 0)
    {
        std::cerr << SDL_GetError() << std::endl;
        return Vector2u(0, 0);
    }

    return Vector2u(static_cast<unsigned int>(width),
                    static_cast<unsigned int>(height));
}

Purity::Texture::~Texture()
{
    SDL_DestroyTexture(mInternalTexture);
}
