#include "text.h"

Purity::Text::Text()
{
}

Purity::Text::Text(const std::string& str, const Font& font)
    : mTextStr(str)
    , mFont(font)
{
}

void Purity::Text::setText(const std::string& str)
{
    mTextStr = str;
}

std::string Purity::Text::getText() const
{
    return mTextStr;
}

void Purity::Text::setFont(const Purity::Font& font)
{
    mFont = font;
}

Purity::Font Purity::Text::getFont() const
{
    return mFont;
}
