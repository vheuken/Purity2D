#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <SFML/Graphics.hpp>
#include "object.h"
#include "movableobject.h"

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
    class ObjectManager : public sf::Drawable
    {
    public:
        ObjectManager(const Tmx::Map* tmxMap, b2World* world);

        const Entity* getObjectByName(const std::string& objectName);
        MovableEntity* getMovableObjectByName(const std::string& objectName);
        void updatePhysics();

        static luabind::scope luaBindings();

    private:
        const Tmx::Map* mTmxMap;
        b2World* mWorld;
        std::vector<Entity> mObjectList;
        std::vector<MovableEntity> mMovableObjectList;

        void initializeObjects();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };
}

#endif // OBJECT_MANAGER_H