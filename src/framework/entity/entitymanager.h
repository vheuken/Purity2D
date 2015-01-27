#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <memory>
#include <vector>
#include <lua.hpp>

#include "entity.h"
#include "movableentity.h"
#include "../graphics/texturemanager.h"
#include "entitystate.h"
#include "../graphics/drawable.h"

class b2World;

namespace luabind
{
struct scope;
}

namespace Tmx
{
class Map;
}

namespace Purity
{
class EntityManager : public Drawable
{
public:
    EntityManager(const Tmx::Map* tmxMap, b2World* world);

    Entity* getEntityByName(const std::string& objectName);
    MovableEntity* getMovableEntityByName(const std::string& objectName);
    MovableEntity* getMovableEntityById(unsigned int id);

    void destroyEntity(unsigned int id);

    void updatePhysics();

    std::vector<EntityState> getEntityStates() const;

    static void luaBindings(lua_State* state);

private:
    const Tmx::Map* mTmxMap;
    b2World* mWorld;
    std::vector<std::unique_ptr<Entity>> mEntityList;
    std::vector<std::unique_ptr<MovableEntity>> mMovableEntityList;

    TextureManager mTextureManager;

    void initializeObjects();

    virtual void draw(RenderTarget& target) const;
};
}

#endif // OBJECT_MANAGER_H
