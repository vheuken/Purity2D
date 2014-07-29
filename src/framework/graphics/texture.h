#ifndef PURITY_TEXTURE_H
#define PURITY_TEXTURE_H

#include <string>

#include "renderer.h"

#include "../system/vector2.h"

struct SDL_Texture;
struct SDL_Surface;

namespace Purity
{
    class Texture : protected Renderer
    {
    public:
        ~Texture();

        bool loadFromFile(const std::string& path);

        Vector2u getSize() const;

        explicit operator SDL_Texture*() const;

    private:
        SDL_Texture* mInternalTexture;

        SDL_Surface* loadImage(const std::string& path);
    };
}

#endif // PURITY_TEXTURE_H
