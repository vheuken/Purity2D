#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <boost/filesystem.hpp>
#include <SFML/Graphics.hpp>

namespace Purity
{
    class GameMap;
    
    class Scene : public sf::Drawable
    {
    public:
        Scene(const boost::filesystem::path& sceneDir);

    private:
        std::unique_ptr<GameMap> mMap;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };

}

#endif // SCENE_H