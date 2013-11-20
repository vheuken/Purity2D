#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>
#include <memory>
#include <mutex>
#include <boost/filesystem.hpp>
#include <SFML/Graphics.hpp>
#include <TmxParser/TmxMap.h>
#include "gamemap.h"
#include "objectmanager.h"

class b2World;
class b2Body;

namespace Purity
{
    const std::string DEFAULT_MAP_FILENAME = "map.tmx";
    const std::string DEFAULT_EVENT_HANDLER_FILENAME = "eventHandler.lua";
    const std::string DEFAULT_EVENT_HANDLER_FUNCTION_NAME = "eventHandler";
	const std::string DEFAULT_ON_PHYSICS_UPDATE_SCRIPT = "onPhysicsUpdate.lua";

    class Scene : public sf::Drawable
    {
    public:
        Scene(const boost::filesystem::path& sceneDir);

        void initializePhysics(b2World * world);
        void updatePhysics();

        std::string getLuaEventHandlerPath() const;
        std::string getLuaEventHandlerFunctionName() const;
		std::string getLuaPhysicsUpdatePath() const;

    private:
        std::unique_ptr<Tmx::Map> mTmxMap;
        std::unique_ptr<GameMap> mMap;
        std::unique_ptr<ObjectManager> mObjectManager;

        boost::filesystem::path mLuaEventHandlerFile;
		boost::filesystem::path mLuaPhysicsUpdateFile;

        mutable std::mutex mMutex;

        void initializeTiles(b2World* world);
        void initializeObjects(b2World* world);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };

}

#endif // SCENE_H
