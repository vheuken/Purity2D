#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <memory>
#include <SFML/Graphics.hpp>
#include <boost/filesystem.hpp>

namespace Tmx
{
    class Map;
}

namespace Purity
{
    class SpriteSheet;

    class GameMap : public sf::Drawable
    {
    public:
        GameMap(const boost::filesystem::path& path);

    private:
        std::unique_ptr<Tmx::Map> mTmxMap;
        std::map<std::string, std::unique_ptr<SpriteSheet> > mTilesetMap;

        sf::Sprite getTile(int x, int y, int layerNum) const;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void drawTiles(sf::RenderTarget& target, sf::RenderStates states) const;
    };

}

#endif // GAME_MAP_H