#ifndef LAYER_H
#define LAYER_H

#include <map>
#include <unordered_map>
#include <memory>
#include <boost/filesystem.hpp>
#include <SFML/Graphics.hpp>

#include "tile.h"
#include "graphics/drawable.h"

class b2World;

namespace Tmx
{
    class Map;
    class Layer;
}

namespace Purity
{
    class TextureManager;

    class Layer : public Drawable
    {
    public:
        Layer(const Tmx::Map * tmxMap, const Tmx::Layer * tmxLayer, TextureManager * textureManager, boost::filesystem::path sceneDir);

        void initializePhysics(b2World * world);

    private:
        std::map<int, std::map<int, std::unique_ptr<Tile> > > mTiles;

        const Tmx::Map * mTmxMap;
        const Tmx::Layer * mTmxLayer;
        TextureManager * mTextureManager;
        boost::filesystem::path mSceneDir;

        void processTiles();

        const Tile * getTile(int x, int y) const;
        std::vector<std::pair<int, int> > getListOfTilesToDraw(const sf::View& view) const;

        virtual void draw(RenderTarget& target) const;
    };
}

#endif // LAYER_H
