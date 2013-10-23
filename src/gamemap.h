#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <boost/filesystem.hpp>
#include <TmxParser/Tmx.h>

#include "spritesheet.h"
#include "texturemanager.h"
#include "tile.h"

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
        std::vector<std::unique_ptr<Tile> > mTileList;

        TextureManager mTextureManager;

        void processTilesetsFromTMXMap();
        void processTiles();

        sf::Sprite getTileSprite(int x, int y, int layerNum) const;


        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void drawTiles(sf::RenderTarget& target, sf::RenderStates states) const;
    };

}

#endif // GAME_MAP_H
