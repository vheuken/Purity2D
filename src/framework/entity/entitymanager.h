#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <SFML/Graphics.hpp>
#include "entity.h"
#include "movableentity.h"
#include "../texturemanager.h"
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

        Entity* const getEntityByName(const std::string& objectName);
        MovableEntity* const getMovableEntityByName(const std::string& objectName);
        MovableEntity* const getMovableEntityById(unsigned int id);

        void updatePhysics();

        std::vector<EntityState> getEntityStates() const;

        static luabind::scope luaBindings();

    private:
        const Tmx::Map* mTmxMap;
        b2World* mWorld;
        std::vector<Entity> mEntityList;
        std::vector<MovableEntity> mMovableEntityList;

        TextureManager mTextureManager;

        void initializeObjects();

        virtual void draw(RenderTarget& target) const;
    };
}

#endif // OBJECT_MANAGER_H
