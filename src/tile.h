#ifndef TILE_H
#define TILE_H

#include "entity.h"

namespace Purity
{
    class Tile : public Entity
    {
    public:
        Tile(int x, int y, int width, int height, const sf::Texture * texture);

        void initializePhysics(b2World * world);

    private:
        void createBody(b2World* world);
    };
}

#endif // TILE_H