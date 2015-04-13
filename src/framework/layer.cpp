#include "layer.h"

#include <Tmx.h>

#include "graphics/texturemanager.h"

Purity::Layer::Layer(const Tmx::Map* tmxMap,
                     const Tmx::Layer* tmxLayer,
                     b2World* world,
                     TextureManager* textureManager,
                     std::string sceneDir,
                     EntityManager* entityManager)
    : mTmxMap(tmxMap)
    , mTmxLayer(tmxLayer)
    , mWorld(world)
    , mTextureManager(textureManager)
    , mSceneDir(sceneDir)
    , mEntityManager(entityManager)
{
    processTiles();
}

void Purity::Layer::processTiles()
{
    Tmx::MapTile tmxTile;

    int layerHeight = mTmxLayer->GetHeight();
    int layerWidth = mTmxLayer->GetWidth();

    for (int y = 0; y < layerHeight; ++y)
    {
        for (int x = 0; x < layerWidth; ++x)
        {
            tmxTile = mTmxLayer->GetTile(x, y);

            if (tmxTile.tilesetId != -1)
            {
                std::string tilesetPathStr
                    = mTmxMap->GetTileset(tmxTile.tilesetId)->GetImage()->GetSource();
                std::string texturePathStr = mSceneDir + tilesetPathStr;

                createTile(x, y, texturePathStr, tmxTile.id);
            }
        }
    }
}

void Purity::Layer::createTile(int x, int y, std::string tileTexturePath, int id)
{
    int tileWidth = mTmxMap->GetTileWidth();
    int tileHeight = mTmxMap->GetTileHeight();

    std::unique_ptr<Tile> tile(
        new Tile(x, y, tileWidth, tileHeight, mTextureManager->getTexture(tileTexturePath), id));

    std::pair<int, int> tileCoordinates(tile->getPosition().x, tile->getPosition().y);

    mTiles[tileCoordinates] = std::move(tile);

    if (mTmxLayer->GetProperties().GetIntProperty("Collidable") == 1)
    {
        mTiles[tileCoordinates]->initializePhysics(mWorld);
    }
    else
    {
        mTiles[tileCoordinates]->initializeStatic();
    }
}

void Purity::Layer::clearTiles()
{
    mTiles.clear();
}

const Purity::Tile* Purity::Layer::getTile(int x, int y) const
{
    std::pair<int, int> tileCoordinates(x, y);

    auto tileIterator = mTiles.find(tileCoordinates);

    if (tileIterator != mTiles.end())
    {
        return tileIterator->second.get();
    }

    return nullptr;
}

void Purity::Layer::draw(Purity::RenderTarget& target) const
{
    for (const auto& it : mTiles)
    {
        target.draw(*it.second);
    }
}
