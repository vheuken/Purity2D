#include "spritesheet.h"

Purity::SpriteSheet::SpriteSheet(const Texture* texture,
                                 int tileWidth,
                                 int tileHeight)
{
    mTileWidth  = tileWidth;
    mTileHeight = tileHeight;

    mTexture = texture;
}

Purity::Rect Purity::SpriteSheet::getTileSubRect(int tileId) const
{
    Rect tileRect;

    tileRect.position.x = ((tileId) % getNumOfRows()) * getTileWidth();
    tileRect.position.y = ((tileId) / getNumOfRows()) * getTileHeight();

    tileRect.width  = getTileWidth();
    tileRect.height = getTileHeight();

    return tileRect;
}

const Purity::Texture* Purity::SpriteSheet::getTexture() const
{
    return mTexture;
}

int Purity::SpriteSheet::getTileWidth() const
{
    return mTileWidth;
}

int Purity::SpriteSheet::getTileHeight() const
{
    return mTileHeight;
}

int Purity::SpriteSheet::getNumOfRows() const
{
    return mTexture->getSize().x / getTileWidth();
}

int Purity::SpriteSheet::getNumOfCols() const
{
    return mTexture->getSize().x / getTileWidth();
}
