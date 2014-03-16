#include "gamemap.h"

#include <TmxParser/Tmx.h>

Purity::GameMap::GameMap(const Tmx::Map* tmxMap, const boost::filesystem::path& sceneDir)
    : mSceneDir(sceneDir), mTmxMap(tmxMap), mTextureManager(new TextureManager())
{
    //processTilesetsFromTMXMap();
    processLayers();
}

void Purity::GameMap::initializeTilePhysics(b2World * world)
{
    for (auto it = mLayersList.begin(); it != mLayersList.end(); it++)
    {
        it->get()->initializePhysics(world);
    }
}

void Purity::GameMap::processLayers()
{
    const std::vector<Tmx::Layer *, std::allocator<Tmx::Layer *> > tmxLayers = mTmxMap->GetLayers();

    for (auto it = tmxLayers.begin(); it != tmxLayers.end(); ++it)
    {
        std::unique_ptr<Layer> layer(new Layer(mTmxMap, *it, mTextureManager.get(), mSceneDir));

        mLayersList.push_back(std::move(layer));
    }
}

void Purity::GameMap::processTilesetsFromTMXMap()
{
    SpriteSheet spriteSheet;
    std::string tilesetFileName;
    const Texture * texture;
    const Tmx::Tileset * tileset;

    for (int i = 0; i < mTmxMap->GetNumTilesets(); ++i)
    {
        tileset = mTmxMap->GetTileset(i);

        tilesetFileName = (tileset->GetImage()->GetSource());

        texture = mTextureManager->getTexture(mSceneDir.string() + tilesetFileName);

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

void Purity::GameMap::draw(Purity::RenderTarget& target) const
{
    for (auto it = mLayersList.begin(); it != mLayersList.end(); ++it)
    {
        target.draw(*it->get());
    }
}
