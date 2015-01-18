#ifndef PURITY_TEXT_H
#define PURITY_TEXT_H

#include <string>
#include "drawable.h"
#include "font.h"

namespace Purity
{
class Text : protected Drawable
{
public:
    Text();
    Text(const std::string& str, const Font& font);

    void setText(const std::string& str);
    std::string getText() const;

    void setFont(const Font& font);
    Font getFont() const;

    void draw(RenderTarget& target) const;

private:
    std::string mTextStr;
    Font mFont;
};
}

#endif // PURITY_TEXT_H
