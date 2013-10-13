#ifndef TILE_H
#define TILE_H

#include <TmxParser/TmxTile.h>

#include "object.h"

namespace Purity
{
    class Tile : public Object
    {
    public:
        Tile(const Tmx::Tile* tile, b2World* world);

    private:
        sf::Sprite mTileSprite;

        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };
}

#endif // TILE_H