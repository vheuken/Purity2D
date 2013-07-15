#include "spritesheet.h"

Purity::SpriteSheet::SpriteSheet()
{
}

Purity::SpriteSheet::SpriteSheet(const sf::Texture& spriteSheetTexture, 
                             int tileWidth, int tileHeight)
{
    this->tileWidth  = tileWidth;
    this->tileHeight = tileHeight;

    spriteSheet.setTexture(spriteSheetTexture);
}

sf::Sprite Purity::SpriteSheet::getTile(int tileId)
{
    // if sprite is already in spriteMap
    if ( isSpriteUsed(tileId) )
    {
        return spriteSheetMap[tileId];
    }

    addSprite(tileId);

    return spriteSheetMap[tileId];
}

sf::Sprite Purity::SpriteSheet::getSpriteSheet()
{
    return spriteSheet;
}

bool Purity::SpriteSheet::isSpriteUsed(int tileID)
{
    std::map<int, sf::Sprite>::iterator found;

    found = spriteSheetMap.find(tileID);

    // if sprite is NOT in the map
    if ( found == spriteSheetMap.end() )
    {
        return false;
    }

    return true;
}

void Purity::SpriteSheet::setSpriteSheetSubRect(int tileId)
{
    // coordinates for left and right of rect
    int leftCoordinate;
    int topCoordinate;

    sf::IntRect rectangle;

    leftCoordinate = ((tileId) % getNumOfRows()) * getTileWidth();
    topCoordinate  = ((tileId) / getNumOfRows()) * getTileHeight();
                    
    rectangle.height = getTileHeight();
    rectangle.width = getTileWidth();
    rectangle.top = topCoordinate;
    rectangle.left = leftCoordinate;

    spriteSheet.setTextureRect(rectangle);
}

void Purity::SpriteSheet::addSprite(int tileId)
{
    
    if (isSpriteUsed(tileId) == false)
    {
        setSpriteSheetSubRect(tileId);
        spriteSheetMap[tileId] = spriteSheet;
    }
    
}

int Purity::SpriteSheet::getTileWidth() const
{
    return tileWidth;
}

int Purity::SpriteSheet::getTileHeight() const
{
    return tileHeight;
}

int Purity::SpriteSheet::getNumOfRows()
{
    return getSpriteSheet().getTexture()->getSize().x / getTileWidth();

}

int Purity::SpriteSheet::getNumOfCols()
{
    return getSpriteSheet().getTexture()->getSize().y / getTileHeight();
}