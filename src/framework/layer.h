#ifndef LAYER_H
#define LAYER_H

#include <map>
#include <utility>
#include <memory>
#include <string>

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
    Layer(const Tmx::Map* tmxMap,
          const Tmx::Layer* tmxLayer,
          b2World* world,
          TextureManager* textureManager,
          std::string sceneDir);

    void createTile(int x, int y, std::string tileTexturePath, int id);

    void clearTiles();

private:
    std::map<std::pair<int, int>, std::unique_ptr<Tile>> mTiles;

    const Tmx::Map* mTmxMap;
    const Tmx::Layer* mTmxLayer;
    b2World* mWorld;
    TextureManager* mTextureManager;
    std::string mSceneDir;

    void processTiles();

    const Tile* getTile(int x, int y) const;

    virtual void draw(RenderTarget& target) const;
};
}

#endif // LAYER_H
