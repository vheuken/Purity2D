#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>
#include <memory>
#include <boost/filesystem.hpp>
#include <SFML/Graphics.hpp>
#include <TmxParser/Tmx.h>
#include <Box2D/Box2D.h>
#include "gamemap.h"
#include "object.h"

namespace Purity
{
    const std::string DEFAULT_MAP_FILENAME = "map.tmx";

    class Scene : public sf::Drawable
    {
    public:
        Scene(const boost::filesystem::path& sceneDir);

        void initializePhysics(b2World * world);
        void updatePhysics();

    private:
        std::unique_ptr<Tmx::Map> mTmxMap;
        std::unique_ptr<GameMap> mMap;

        std::vector<Object> mObjectList;
        std::vector<b2Body *> mTileBodyList;

        void initializeTiles(b2World* world);
        void initializeObjects(b2World* world);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };

}

#endif // SCENE_H
