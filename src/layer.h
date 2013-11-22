#ifndef LAYER_H
#define LAYER_H

#include <unordered_map>
#include <memory>
#include <SFML/Graphics.hpp>

#include "tile.h"

namespace Tmx
{
    class Map;
}

namespace Purity
{
    class Layer : public sf::Drawable
    {
    public:
        const Tile * getTile(int x, int y) const;

    private:
        std::map<int, std::map<int, std::unique_ptr<Tile> > > mTiles;

        const Tmx::Map * mTmxMap;

        std::vector<std::pair<int, int> > getListOfTilesToDraw(const sf::View& view) const;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };
}

#endif // LAYER_H