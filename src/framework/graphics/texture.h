#ifndef PURITY_TEXTURE_H
#define PURITY_TEXTURE_H

struct SDL_Texture;

namespace Purity
{
    class Texture
    {
    public:
        Texture();
    private:
        SDL_Texture * mTexture;
    };
}

#endif // PURITY_TEXTURE_H
