#include "font.h"

#include <iostream>
#include <string>
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>
#include <SDL.h>

Purity::Font::Font()
{
}

Purity::Font::Font(const std::string& fontFileName)
    : mFontFileName(fontFileName)
{
    loadFont();

    if (!stbtt_InitFont(&mFontInfo, mFontData.data(), 0))
    {
        std::cerr << "Failed to initialize font" << std::endl;
    }

    int w, h;
    auto bitmap = stbtt_GetCodepointBitmap(&mFontInfo, 0, stbtt_ScaleForPixelHeight(&mFontInfo, 30),
                                           'D', &w, &h, 0, 0);
    for (int j = 0; j < h; ++j)
    {
        for (int i = 0; i < w; ++i)
            putchar(" .:ioVM@"[bitmap[j * w + i] >> 5]);
        putchar('\n');
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
    mFontData.reserve(fontFileSize);

    fontFile->read(fontFile, &mFontData[0], 1, fontFileSize);

    fontFile->close(fontFile);
}

SDL_Surface* Purity::Font::getSurface() const
{
    return mSurface;
}
