#include "layer.h"

#include <TmxParser/Tmx.h>

#include "graphics/texturemanager.h"

Purity::Layer::Layer(const Tmx::Map* tmxMap,
                     const Tmx::Layer* tmxLayer,
                     b2World* world,
                     TextureManager* textureManager,
                     std::string sceneDir)
    : mTmxMap(tmxMap)
    , mTmxLayer(tmxLayer)
    , mWorld(world)
    , mTextureManager(textureManager)
    , mSceneDir(sceneDir)
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

            if (tmxTile.id != 0)
            {
                std::string tilesetPathStr
                    = mTmxMap->GetTileset(tmxTile.tilesetId)->GetImage()->GetSource();
                std::string texturePathStr = mSceneDir + tilesetPathStr;

                // Tile tile(x, y, tileWidth, tileHeight, tileTexture, tmxTile.id);
                // addTile(tile)
                createTile(x, y, texturePathStr, tmxTile.id);
            }
        }
    }
}

void Purity::Layer::initializePhysics(b2World* world)
{
    /*
    if (mTmxLayer->GetProperties().GetNumericProperty("Collidable") == 1)
    {
        for (auto it = mTiles.begin(); it != mTiles.end(); ++it)
        {
            it->second->initializePhysics(world);
        }
    }
    else
    {
        for (auto it = mTiles.begin(); it != mTiles.end(); ++it)
        {
            it->second->initializeStatic();
        }
    }*/
}

void Purity::Layer::createTile(int x, int y, std::string tileTexturePath, int id)
{
    int tileWidth = mTmxMap->GetTileWidth();
    int tileHeight = mTmxMap->GetTileHeight();

    std::unique_ptr<Tile> tile(new Tile(x, y, tileWidth, tileHeight, mTextureManager->getTexture(tileTexturePath), id));

    std::pair<int, int> tileCoordinates(tile->getPosition().x, tile->getPosition().y);

    mTiles[tileCoordinates] = std::move(tile);

    if (mTmxLayer->GetProperties().GetNumericProperty("Collidable") == 1)
    {
        mTiles[tileCoordinates]->initializePhysics(mWorld);
    }
    else
    {
        mTiles[tileCoordinates]->initializeStatic();
    }
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
