#ifndef LAYER_H
#define LAYER_H

#include <map>
#include <unordered_map>
#include <memory>
#include <SFML/Graphics.hpp>

#include "tile.h"

class b2World;

namespace Tmx
{
    class Map;
    class Layer;
}

namespace Purity
{
    class TextureManager;

    class Layer : public sf::Drawable
    {
    public:
        Layer(const Tmx::Map * tmxMap, const Tmx::Layer * tmxLayer, TextureManager * textureManager);

        void initializePhysics(b2World * world);

    private:
        std::map<int, std::map<int, std::unique_ptr<Tile> > > mTiles;

        const Tmx::Map * mTmxMap;
        const Tmx::Layer * mTmxLayer;
        TextureManager * mTextureManager;

        void processTiles();

        const Tile * getTile(int x, int y) const;
        std::vector<std::pair<int, int> > getListOfTilesToDraw(const sf::View& view) const;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };
}

#endif // LAYER_H