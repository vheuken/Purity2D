#include "layer.h"

#include <TmxParser/Tmx.h>

#include "texturemanager.h"

Purity::Layer::Layer(const Tmx::Map * tmxMap, const Tmx::Layer * tmxLayer,  TextureManager * textureManager )
    : mTmxMap(tmxMap), mTmxLayer(tmxLayer), mTextureManager(textureManager)
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

    for (int y = 0; y < layerHeight; y++)
    {
        std::map<int, std::unique_ptr<Tile>> col;

        for (int x = 0; x < layerWidth; x++)
        {
            tmxTile = mTmxLayer->GetTile(x, y);
            
            if (tmxTile.id != 0)
            {
                tileTexture = mTextureManager->getTexture(mTmxMap->GetTileset(tmxTile.tilesetId)->GetImage()->GetSource());
                
                std::unique_ptr<Tile> tile(new Tile(x, y, tileWidth, tileHeight, tileTexture));

                col[x] = std::move(tile);
            }
        }
        mTiles[y] = std::move(col);
    }
}

const Purity::Tile * Purity::Layer::getTile(int x, int y) const
{
    auto row = mTiles.find(y);

    if ( row != mTiles.end() )
    {
        auto col = row->second.find(x);

        if ( col != row->second.end() )
        {
            return col->second.get();
        }
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

void Purity::Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    std::vector<std::pair<int, int> > listOfTilesToDraw = getListOfTilesToDraw(target.getView());

    for (auto it = listOfTilesToDraw.begin(); it != listOfTilesToDraw.end(); it++)
    {
        const Tile * tile = getTile(it->first, it->second);

        if (tile != nullptr)
        {
            target.draw(*tile);
        }
    }
}