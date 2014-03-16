#ifndef PURITY_TEXTURE_H
#define PURITY_TEXTURE_H

#include <string>

#include "../system/vector2.h"

struct SDL_Texture;

namespace Purity
{
    class Texture
    {
    public:
        bool loadFromFile(const std::string& path);

        Vector2u getSize() const;

    private:
        SDL_Texture * mTexture;
    };
}

#endif // PURITY_TEXTURE_H
