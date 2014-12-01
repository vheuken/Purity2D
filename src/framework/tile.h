#ifndef TILE_H
#define TILE_H

#include "entity/entity.h"

namespace Purity
{
class Tile : public Entity
{
public:
    Tile() {}
    Tile(int x, int y, int width, int height, Texture* texture, int id);

    void initializePhysics(b2World* world);
    void initializeStatic();

private:
    int mTileId;

    void setTextureSubrect();

    void createBody(b2World* world);
};
}

#endif // TILE_H
