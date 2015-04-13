#ifndef PURITY_FONT_H
#define PURITY_FONT_H

#include <string>
#include <vector>
#include <stb_truetype.h>

struct SDL_Surface;

namespace Purity
{
class Font
{
public:
    Font();
    Font(const std::string& fontFileName);

    SDL_Surface* getSurface() const;

private:
    std::string mFontFileName;

    stbtt_fontinfo mFontInfo;

    std::vector<unsigned char> mFontData;

    SDL_Surface* mSurface;

    void loadFont();
};
}

#endif // PURITY_FONT_H
