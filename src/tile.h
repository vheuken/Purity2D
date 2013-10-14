#ifndef TILE_H
#define TILE_H

#include <TmxParser/TmxTile.h>

#include "object.h"

namespace Purity
{
    class Tile : public Object
    {
    public:
        Tile(const Tmx::MapTile& tile, const sf::Sprite& tileSprite);

    private:
        sf::Sprite mTileSprite;

        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };
}

#endif // TILE_H