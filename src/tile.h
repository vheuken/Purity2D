#ifndef TILE_H
#define TILE_H

#include "object.h"

namespace Purity
{
    class Tile : public Object
    {
    public:
        Tile(int x, int y, int width, int height, const sf::Sprite& tileSprite);

        void initializePhysics(b2World * world);

    private:
        sf::Sprite mTileSprite;

        void createBody(b2World* world);

        bool isInView(const sf::View& view) const;

        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };
}

#endif // TILE_H