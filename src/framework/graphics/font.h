#ifndef PURITY_FONT_H
#define PURITY_FONT_H

#include <string>

namespace Purity
{
class Font
{
public:
    Font(const std::string& fontFileName);

private:
    const std::string mFontFileName;
};
}

#endif // PURITY_FONT_H
