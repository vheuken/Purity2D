#include "gamemap.h"


Purity::GameMap::GameMap(const Tmx::Map* tmxMap, const boost::filesystem::path& sceneDir)
    : mSceneDir(sceneDir)
{
    mTmxMap = tmxMap;

    processTilesetsFromTMXMap();
}

void Purity::GameMap::processTilesetsFromTMXMap()
{
    SpriteSheet spriteSheet;
    std::string tilesetFileName;
    const sf::Texture * texture;
    const Tmx::Tileset * tileset;

    for (int i = 0; i < mTmxMap->GetNumTilesets(); i++)
    {
        tileset = mTmxMap->GetTileset(i);

        tilesetFileName = (tileset->GetImage()->GetSource());
        
        texture = textureManager.getTexture(mSceneDir.string() + tilesetFileName);

        spriteSheet = SpriteSheet(*texture);
        
        mTilesetMap[mSceneDir.string() + tilesetFileName] = spriteSheet;

    }
}

sf::Sprite Purity::GameMap::getTile(int x, int y, int layerNum) const
{
        Tmx::MapTile tile;
        const Tmx::Tileset* tileset;
        SpriteSheet spriteSheet;
        sf::Sprite tileSprite;
        float tilePositionX;
        float tilePositionY;
        std::string imagePath;

        tile = mTmxMap->GetLayer(layerNum)->GetTile(x, y);
        
        if (tile.id == 0)
        {
                return tileSprite;
        }

        tileset = mTmxMap->GetTileset(tile.tilesetId);
        
        imagePath = (mSceneDir.string() + tileset->GetImage()->GetSource());

        spriteSheet = mTilesetMap.at(imagePath);

        tileSprite = spriteSheet.getTile(tile.id);

        tilePositionX = x * spriteSheet.getTileWidth();
        tilePositionY = y * spriteSheet.getTileHeight();

        tileSprite.setPosition(tilePositionX, tilePositionY);
        
        return tileSprite;

}

void Purity::GameMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    drawTiles(target, states);
}

void Purity::GameMap::drawTiles(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Sprite tile;
    sf::View view = target.getView();
    int layerCount = mTmxMap->GetNumLayers();

    int tileResolutionX = (int)view.getSize().x / mTmxMap->GetTileWidth();
    int tileResolutionY = (int)view.getSize().y / mTmxMap->GetTileHeight();

    int startingTileX = (int)(view.getCenter().x - view.getSize().x/2) / mTmxMap->GetTileWidth();
    int startingTileY = (int)(view.getCenter().y - view.getSize().y/2) / mTmxMap->GetTileHeight();

    int endTileX = startingTileX + tileResolutionX;
    int endTileY = startingTileY + tileResolutionY;
    
    for (int layerNum = 0; layerNum < layerCount; layerNum++)
    {
        for (int y = startingTileY; y < endTileY; y++)
        {
            for (int x = startingTileX; x < endTileX; x++)
            {
                tile = getTile(x, y, layerNum);
                target.draw(tile);
            }
        }
    }
}
