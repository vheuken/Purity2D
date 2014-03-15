#include "layer.h"

#include <TmxParser/Tmx.h>

#include "texturemanager.h"

Purity::Layer::Layer(const Tmx::Map * tmxMap, const Tmx::Layer * tmxLayer,  TextureManager * textureManager, boost::filesystem::path sceneDir )
: mTmxMap(tmxMap), mTmxLayer(tmxLayer), mTextureManager(textureManager), mSceneDir(sceneDir)
{
    processTiles();
}

void Purity::Layer::processTiles()
{
    const sf::Texture * tileTexture;
    Tmx::MapTile tmxTile;

    int layerHeight = mTmxLayer->GetHeight();
    int layerWidth = mTmxLayer->GetWidth();
    int tileWidth = mTmxMap->GetTileWidth();
    int tileHeight = mTmxMap->GetTileHeight();

    for (int y = 0; y < layerHeight; ++y)
    {
        for (int x = 0; x < layerWidth; ++x)
        {
            tmxTile = mTmxLayer->GetTile(x, y);

            if (tmxTile.id != 0)
            {
                tileTexture = mTextureManager->getTexture(mSceneDir.string() + mTmxMap->GetTileset(tmxTile.tilesetId)->GetImage()->GetSource());

                std::unique_ptr<Tile> tile(new Tile(x, y, tileWidth, tileHeight, tileTexture, tmxTile.id));

                std::pair<int, int> tileCoordinates(x, y);

                mTiles[tileCoordinates] = std::move(tile);
            }
        }
    }
}

void Purity::Layer::initializePhysics(b2World * world)
{
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
    }
}

const Purity::Tile * Purity::Layer::getTile(int x, int y) const
{
    std::pair <int, int> tileCoordinates(x, y);

    auto tileIterator = mTiles.find(tileCoordinates);

    if ( tileIterator != mTiles.end() )
    {
        return tileIterator->second.get();
    }

    return nullptr;
}

std::vector<std::pair<int, int> > Purity::Layer::getListOfTilesToDraw(const sf::View& view) const
{
    std::vector<std::pair<int, int> > listOfTilesToDraw;

    int tileWidth  = mTmxMap->GetTileWidth();
    int tileHeight = mTmxMap->GetTileHeight();

    sf::Vector2f halfSize(view.getSize().x/2, view.getSize().y/2);

    sf::Vector2f topLeftCorner = view.getCenter() - halfSize;
    sf::Vector2f bottomRightCorner = view.getCenter() + halfSize;

    for (int x = (int)topLeftCorner.x; x < bottomRightCorner.x; x += tileWidth)
    {
        for (int y = (int)topLeftCorner.y; y < bottomRightCorner.y; y += tileHeight)
        {
            std::pair<int, int> tile(x/tileWidth, y/tileWidth);

            listOfTilesToDraw.push_back(tile);
        }
    }

    return listOfTilesToDraw;
}

void Purity::Layer::draw(Purity::RenderTarget& target) const
{
    for (auto it = mTiles.begin(); it != mTiles.end(); ++it)
    {
        target.draw(*it->second.get());
    }
}
