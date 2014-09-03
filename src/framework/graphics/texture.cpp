#include "texture.h"

#include <iostream>
#include <cstring>
#include <SDL.h>
#include <stb_image.h>

Purity::Texture::Texture()
: mInternalTexture(nullptr),
  mTextureCreationNeeded(false)
{
}

void Purity::Texture::loadFromFile(const std::string& path)
{
    mTextureCreationNeeded = true;
    mImageFilePath = path;
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

Purity::Texture::operator SDL_Texture*() const
{
    return mInternalTexture;
}

bool Purity::Texture::createInternalTexture(SDL_Renderer* renderer)
{
    auto surface = loadImage(mImageFilePath);

    if (surface == nullptr)
    {
        std::cerr << "Error loading image" << std::endl;
        return false;
    }

    mInternalTexture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    if (mInternalTexture == nullptr)
    {
        std::cerr << SDL_GetError() << std::endl;
        return false;
    }

    mTextureCreationNeeded = false;

    return true;
}

SDL_Surface* Purity::Texture::loadImage(const std::string& path)
{
    int x, y, comp;
    unsigned char *data;
    uint32_t rmask, gmask, bmask, amask;
    SDL_Surface *rv;

    SDL_RWops* file = SDL_RWFromFile(path.c_str(), "rb");

    if (!file)
    {
        return nullptr;
    }

    int fileSize = file->size(file);
    unsigned char* fileData = new unsigned char[fileSize + 1];
    file->read(file, fileData, 1, fileSize);

    data = stbi_load_from_memory(fileData, fileSize, &x, &y, &comp, 0);
    file->close(file);

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    if (comp == 4) {
        rv = SDL_CreateRGBSurface(0, x, y, 32, rmask, gmask, bmask, amask);
    } else if (comp == 3) {
        rv = SDL_CreateRGBSurface(0, x, y, 24, rmask, gmask, bmask, 0);
    } else {
        stbi_image_free(data);
        return 0;
    }

    memcpy(rv->pixels, data, comp * x * y);

    stbi_image_free(data);
    delete [] fileData;

    return rv;
}
