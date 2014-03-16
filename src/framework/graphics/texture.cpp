#include "texture.h"

#include <SDL.h>

bool Purity::Texture::loadFromFile(const std::string& path)
{
    // TODO: implement
    return true;
}

Purity::Vector2u Purity::Texture::getSize() const
{
    int width, height;

    SDL_QueryTexture(mTexture, NULL, NULL, &width, &height);

    return Vector2u(static_cast<unsigned int>(width),
                    static_cast<unsigned int>(height));
}
