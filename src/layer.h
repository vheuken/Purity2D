#ifndef LAYER_H
#define LAYER_H

#include <unordered_map>
#include <memory>
#include <SFML/Graphics.hpp>

#include "tile.h"

namespace Purity
{
    class Layer : public sf::Drawable
    {
    public:
        const Tile * getTile(int x, int y) const;

    private:
        std::map<int, std::map<int, std::unique_ptr<Tile> > > mTiles;
    };
}

#endif // LAYER_H