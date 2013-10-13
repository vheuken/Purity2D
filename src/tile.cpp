#include "tile.h"

Purity::Tile::Tile(const Tmx::Tile* tile, b2World* world)
{

}

void Purity::Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mTileSprite);
}