#ifndef TILE_H
#define TILE_H

#include <TmxParser/TmxTile.h>

#include "object.h"

namespace Purity
{
    class Tile : public Object
    {
        Tile(const Tmx::Tile* tile, b2World* world);
    };
}

#endif // TILE_H