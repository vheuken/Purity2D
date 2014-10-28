#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <vector>
#include <memory>
#include <string>

#include "spritesheet.h"
#include "graphics/texturemanager.h"
#include "tile.h"
#include "layer.h"

#include "graphics/drawable.h"

class b2World;

namespace Tmx
{
class Map;
}

namespace Purity
{
class GameMap : public Drawable
{
public:
    GameMap(const Tmx::Map* tmxMap, const std::string& sceneDir);

    void initializeTilePhysics(b2World* world);

private:
    const std::string mSceneDir;
    const Tmx::Map* mTmxMap;

    std::map<int, std::map<int, std::unique_ptr<Tile>>> mPhysicsTileList;
    std::map<int, std::map<int, std::unique_ptr<Tile>>> mStaticTileList;

    std::vector<std::unique_ptr<Layer>> mLayersList;

    std::unique_ptr<TextureManager> mTextureManager;

    void processTilesetsFromTMXMap();
    void processLayers();
    void addTilesToList(std::map<int, std::map<int, std::unique_ptr<Tile>>>& tileList,
                        int layerNum);

    virtual void draw(RenderTarget& target) const;
};
}

#endif // GAME_MAP_H
