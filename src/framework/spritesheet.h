#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <map>
#include <iostream>

#include "graphics/texture.h"
#include "graphics/rect.h"

namespace Purity
{
class SpriteSheet
{
public:
    SpriteSheet(Texture* texture, int tileWidth, int tileHeight);

    Rect getTileSubRect(int tileId) const;

    Texture* getTexture() const;

    int getTileWidth() const;
    int getTileHeight() const;

private:
    Texture* mTexture;

    int mTileWidth;
    int mTileHeight;

    int getNumOfRows() const;
    int getNumOfCols() const;
};
}

#endif // SPRITESHEET_H
