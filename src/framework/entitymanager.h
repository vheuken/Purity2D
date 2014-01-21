#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <SFML/Graphics.hpp>
#include "entity.h"
#include "movableentity.h"
#include "texturemanager.h"
#include "entitystate.h"

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
    class EntityManager : public sf::Drawable
    {
    public:
        EntityManager(const Tmx::Map* tmxMap, b2World* world);

        const Entity* getEntityByName(const std::string& objectName);
        MovableEntity* getMovableEntityByName(const std::string& objectName);
        MovableEntity* getMovableEntityById(unsigned int id);

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

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };
}

#endif // OBJECT_MANAGER_H
