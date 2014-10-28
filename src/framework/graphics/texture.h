#ifndef PURITY_TEXTURE_H
#define PURITY_TEXTURE_H

#include <string>
#include "../system/vector2.h"

struct SDL_Texture;
struct SDL_Surface;
struct SDL_Renderer;

namespace Purity
{
class Texture
{
public:
    Texture();
    ~Texture();

    void loadFromFile(const std::string& path);

    Vector2u getSize() const;

    explicit operator SDL_Texture*() const;

private:
    SDL_Texture* mInternalTexture;
    std::string mImageFilePath;
    bool mTextureCreationNeeded;

    bool createInternalTexture(SDL_Renderer* renderer);

    SDL_Surface* loadImage(const std::string& path);

    friend class RenderTarget;
};
}

#endif // PURITY_TEXTURE_H
