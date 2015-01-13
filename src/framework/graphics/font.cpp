#include "font.h"

#include <iostream>
#include <string>
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>
#include <SDL.h>

Purity::Font::Font(const std::string &fontFileName)
    : mFontFileName(fontFileName)
{
    loadFont();

    stbtt_fontinfo font;

    if(!stbtt_InitFont(&font, mFontData.get(), 0))
    {
        std::cerr << "Failed to initialize font" << std::endl;
    }
}

void Purity::Font::loadFont()
{
    SDL_RWops* fontFile = SDL_RWFromFile(mFontFileName.c_str(), "rb");

    if (fontFile == nullptr)
    {
        std::cerr << "Error loading font file"
                  << ": " << SDL_GetError() << std::endl;
    }

    const auto fontFileSize = fontFile->size(fontFile);
    mFontData = std::unique_ptr<unsigned char>(new unsigned char[fontFileSize]);

    fontFile->read(fontFile, mFontData.get(), 1, fontFileSize);

    fontFile->close(fontFile);
}

SDL_Surface* Purity::Font::getSurface() const
{
    return mSurface;
}
