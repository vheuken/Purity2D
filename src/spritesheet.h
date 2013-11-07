#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <map>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace Purity
{

    // default tile size
    const int DEFAULT_TILE_WIDTH  = 16;
    const int DEFAULT_TILE_HEIGHT = 16;

    class SpriteSheet
    {
    private:
        sf::Sprite spriteSheet;
        // map holds multiple "copies" of the same sprite 
        // with a set subrect
        // key value refers to tile ID
        std::map<int, sf::Sprite> spriteSheetMap;

        // checks if sprite si already in spriteSheetMap
        bool isSpriteUsed(int tileId);

        void addSprite(int tileId);
        void setSpriteSheetSubRect(int tileId);

        int getNumOfRows();
        int getNumOfCols();

        int tileWidth;
        int tileHeight;

    public:
        // defualt constructor does nothing
        SpriteSheet();
        SpriteSheet(const sf::Texture& spriteSheetTexture, 
                    int tileWidth = DEFAULT_TILE_WIDTH,
                    int tileHeight = DEFAULT_TILE_HEIGHT);

        // returns a sprite set to the tile's subrect
        sf::Sprite getTile(int tileId);

        // returns spriteSheet
        sf::Sprite getSpriteSheet();

        int getTileWidth()  const;
        int getTileHeight() const;
    };

}

#endif // SPRITESHEET_H