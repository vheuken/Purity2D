#include "layer.h"

#include <TmxParser/Tmx.h>

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

    for (int x = topLeftCorner.x; x < bottomRightCorner.x; x += tileWidth)
    {
        for (int y = topLeftCorner.y; y < bottomRightCorner.y; y += tileHeight)
        {
            std::pair<int, int> tile(x/tileWidth, y/tileWidth);

            listOfTilesToDraw.push_back(tile);
        }
    }

    return listOfTilesToDraw;
}

void Purity::Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    auto listOfTilesToDraw = getListOfTilesToDraw(target.getView());

    for (auto it = listOfTilesToDraw.begin(); it != listOfTilesToDraw.end(); it++)
    {
        const Tile * tile = getTile(it->first, it->second);

        target.draw(*tile);
    }
}