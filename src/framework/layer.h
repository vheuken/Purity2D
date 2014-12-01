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
          TextureManager* textureManager,
          std::string sceneDir);

    void initializePhysics(b2World* world);

    void addTile(Tile& tile);

private:
    std::map<std::pair<int, int>, Tile> mTiles;

    const Tmx::Map* mTmxMap;
    const Tmx::Layer* mTmxLayer;
    TextureManager* mTextureManager;
    std::string mSceneDir;

    void processTiles();

    const Tile* getTile(int x, int y) const;
    // std::vector<std::pair<int, int> > getListOfTilesToDraw(const sf::View& view) const;

    virtual void draw(RenderTarget& target) const;
};
}

#endif // LAYER_H
