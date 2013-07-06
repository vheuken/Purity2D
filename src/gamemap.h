#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <SFML/Graphics.hpp>
#include <boost/filesystem.hpp>

namespace Purity
{

    class GameMap : public sf::Drawable
    {
    public:
        GameMap(const boost::filesystem::path& path);

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };

}

#endif // GAME_MAP_H