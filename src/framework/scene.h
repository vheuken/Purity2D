#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>
#include <memory>
#include <mutex>
#include <TmxParser/TmxMap.h>
#include "gamemap.h"
#include "entity/entitymanager.h"
#include "entity/entitystate.h"
#include "graphics/drawable.h"

class b2World;
class b2Body;

namespace Purity
{
const std::string DEFAULT_MAP_FILENAME = "map.tmx";
const std::string DEFAULT_EVENT_HANDLER_FILENAME = "eventHandler.lua";
const std::string DEFAULT_EVENT_HANDLER_FUNCTION_NAME = "eventHandler";
const std::string DEFAULT_ON_PHYSICS_UPDATE_SCRIPT = "onPhysicsUpdate.lua";

class Scene : public Drawable
{
public:
    Scene(const std::string& sceneDir);

    void initializePhysics(b2World* world);
    void updatePhysics();

    void setEntityState(const EntityState& state);

    std::vector<EntityState> getEntityStates() const;

    std::string getLuaEventHandlerPath() const;
    std::string getLuaEventHandlerFunctionName() const;
    std::string getLuaPhysicsUpdatePath() const;

private:
    std::unique_ptr<Tmx::Map> mTmxMap;
    std::unique_ptr<GameMap> mMap;
    std::unique_ptr<EntityManager> mObjectManager;

    std::string mLuaEventHandlerFile;
    std::string mLuaPhysicsUpdateFile;

    mutable std::mutex mMutex;

    void initializeTiles(b2World* world);
    void initializeObjects(b2World* world);
    virtual void draw(RenderTarget& target) const;
};
}

#endif // SCENE_H
