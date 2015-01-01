#include "font.h"

#include <iostream>
#include <string>
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>
#include <SDL.h>

Purity::Font::Font(const std::string &fontFileName)
    : mFontFileName(fontFileName)
{
    SDL_RWops* fontFile = SDL_RWFromFile(mFontFileName.c_str(), "rb");

    if (fontFile == nullptr)
    {
        std::cerr << "Error loading font file" << mFontFileName
                  << ": " << SDL_GetError() << std::endl;
    }

    const auto fontFileSize = fontFile->size(fontFile);
    const auto fontData = new unsigned char[fontFileSize];

    fontFile->read(fontFile, fontData, 1, fontFileSize);

    fontFile->close(fontFile);

    stbtt_fontinfo font;

    if(!stbtt_InitFont(&font, fontData, 0))
    {
        std::cerr << "Failed to initialize font" << std::endl;
    }

    delete fontData;
}
