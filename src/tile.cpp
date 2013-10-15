#include "tile.h"

Purity::Tile::Tile(const Tmx::MapTile& tile, const sf::Sprite& tileSprite)
{
    mTileSprite = tileSprite;
    
}

void Purity::Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mTileSprite);
}