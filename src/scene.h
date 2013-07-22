#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>
#include <memory>
#include <mutex>
#include <boost/filesystem.hpp>
#include <SFML/Graphics.hpp>
#include <TmxParser/Tmx.h>
#include <Box2D/Box2D.h>
#include "gamemap.h"
#include "objectmanager.h"

namespace Purity
{
    const std::string DEFAULT_MAP_FILENAME = "map.tmx";
    const std::string DEFAULT_EVENT_HANDLER_FILENAME = "eventHandler.lua";
    const std::string DEFAULT_EVENT_HANDLER_FUNCTION_NAME = "eventHandler";

    class Scene : public sf::Drawable
    {
    public:
        Scene(const boost::filesystem::path& sceneDir);

        void initializePhysics(b2World * world);
        void updatePhysics();

        std::string getLuaEventHandlerPath() const;
        std::string getLuaEventHandlerFunctionName() const;

    private:
        std::unique_ptr<Tmx::Map> mTmxMap;
        std::unique_ptr<GameMap> mMap;
        std::unique_ptr<ObjectManager> mObjectManager;

        std::vector<b2Body *> mTileBodyList;

        boost::filesystem::path mLuaEventHandlerFile;

        mutable std::mutex mMutex;

        void initializeTiles(b2World* world);
        void initializeObjects(b2World* world);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };

}

#endif // SCENE_H
