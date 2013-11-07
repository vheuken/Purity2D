#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <TmxParser/Tmx.h>
#include <luabind/luabind.hpp>
#include "object.h"
#include "movableobject.h"

namespace Purity
{
    class ObjectManager : public sf::Drawable
    {
    public:
        ObjectManager(const Tmx::Map* tmxMap, b2World* world);

        const Object* getObjectByName(const std::string& objectName);
        MovableObject* getMovableObjectByName(const std::string& objectName);
        void updatePhysics();

        static luabind::scope luaBindings();

    private:
        const Tmx::Map* mTmxMap;
        b2World* mWorld;
        std::vector<Object> mObjectList;
        std::vector<MovableObject> mMovableObjectList;

        void initializeObjects();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };
}

#endif // OBJECT_MANAGER_H