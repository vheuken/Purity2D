#include "layer.h"

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