#ifndef PURITY_FONT_H
#define PURITY_FONT_H

#include <string>
#include <memory>

struct SDL_Surface;

namespace Purity
{
class Font
{
public:
    Font(const std::string& fontFileName);

    SDL_Surface* getSurface() const;
private:
    const std::string mFontFileName;

    void loadFont();

    std::unique_ptr<unsigned char> mFontData;

    SDL_Surface* mSurface;
};
}

#endif // PURITY_FONT_H
