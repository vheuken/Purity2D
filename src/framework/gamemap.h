#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <boost/filesystem.hpp>

#include "spritesheet.h"
#include "texturemanager.h"
#include "tile.h"
#include "layer.h"

class b2World;

namespace Tmx
{
    class Map;
}

namespace Purity
{
    class GameMap : public sf::Drawable
    {
    public:
        GameMap(const Tmx::Map* tmxMap, const boost::filesystem::path& sceneDir);

        void initializeTilePhysics(b2World * world);

    private:
        const boost::filesystem::path mSceneDir;
        const Tmx::Map * mTmxMap;
        std::map<std::string, SpriteSheet> mTilesetMap;

        std::map<int, std::map<int, std::unique_ptr<Tile> > > mPhysicsTileList;
        std::map<int, std::map<int, std::unique_ptr<Tile> > > mStaticTileList;

        std::vector<std::unique_ptr<Layer> > mLayersList;

        std::unique_ptr<TextureManager> mTextureManager;

        void processTilesetsFromTMXMap();
        void processLayers();
        void addTilesToList(std::map<int, std::map<int, std::unique_ptr<Tile> > >& tileList, int layerNum);

        sf::Sprite getTileSprite(int x, int y, int layerNum) const;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };

}

#endif // GAME_MAP_H
