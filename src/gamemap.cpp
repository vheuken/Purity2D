#include "gamemap.h"


Purity::GameMap::GameMap(const Tmx::Map* tmxMap, const boost::filesystem::path& sceneDir)
    : mSceneDir(sceneDir)
{
    mTmxMap = tmxMap;

    processTilesetsFromTMXMap();
    processTiles();
}

void Purity::GameMap::initializeTilePhysics(b2World * world)
{
    for (auto it = mPhysicsTileList.begin(); it != mPhysicsTileList.end(); it++)
    {
        it->get()->initializePhysics(world);
    }
}

void Purity::GameMap::processTiles()
{
    int layerCount = mTmxMap->GetNumLayers();

    for (int layerNum = 0; layerNum < layerCount; layerNum++)
    {
        if (mTmxMap->GetLayer(layerNum)->GetProperties().GetNumericProperty("Collidable"))
        {
            addTilesToList(mPhysicsTileList, layerNum);
        }
        else
        {
            addTilesToList(mStaticTileList, layerNum);
        }
    }
}

void Purity::GameMap::addTilesToList(std::vector<std::unique_ptr<Tile> >& tileList, int layerNum)
{
    sf::Sprite tileSprite;
    Tmx::MapTile tmxTile;

    int mapHeight = mTmxMap->GetHeight();
    int mapWidth = mTmxMap->GetWidth();

    for (int y = 0; y < mapHeight; y++)
    {
        for (int x = 0; x < mapWidth; x++)
        {
            tmxTile = mTmxMap->GetLayer(layerNum)->GetTile(x, y);

            if (tmxTile.id != 0)
            {
                int tileWidth = mTmxMap->GetTileWidth();
                int tileHeight = mTmxMap->GetTileHeight();

                tileSprite = getTileSprite(x, y, layerNum);

                tileList.push_back(std::unique_ptr<Tile>(new Tile(x, y, tileWidth, tileHeight, tileSprite)));
            }
        }
    }
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
        
        texture = mTextureManager.getTexture(mSceneDir.string() + tilesetFileName);

        spriteSheet = SpriteSheet(*texture);
        
        mTilesetMap[mSceneDir.string() + tilesetFileName] = spriteSheet;
    }
}

sf::Sprite Purity::GameMap::getTileSprite(int x, int y, int layerNum) const
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
    
    tilePositionX = (float)(x * spriteSheet.getTileWidth());
    tilePositionY = (float)(y * spriteSheet.getTileHeight());
    
    tileSprite.setPosition(tilePositionX, tilePositionY);

    return tileSprite;
}

void Purity::GameMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto it = mStaticTileList.begin(); it != mStaticTileList.end(); it++)
    {
        target.draw(*it->get());
    }

    for (auto it = mPhysicsTileList.begin(); it != mPhysicsTileList.end(); it++)
    {
        target.draw(*it->get());
    }
}