#include "entitymanager.h"

#include <luabind/luabind.hpp>
#include <TmxParser/Tmx.h>
#include "../engine/luamanager.h"

Purity::EntityManager::EntityManager(const Tmx::Map* tmxMap, b2World* world)
{
    mTmxMap = tmxMap;
    mWorld = world;

    initializeObjects();

    luabind::globals(LuaManager::getManager()->getState())["GEntityManager"] = this;
}

const Purity::Entity* Purity::EntityManager::getObjectByName(const std::string& objectName)
{

    for (auto it = mObjectList.begin(); it != mObjectList.end(); it++)
    {
        if (it->getName() == objectName)
        {
            return &*it;
        }
    }

    return nullptr;
}

Purity::MovableEntity* Purity::EntityManager::getMovableObjectByName(const std::string& objectName)
{

    for (auto it = mMovableObjectList.begin(); it != mMovableObjectList.end(); it++)
    {
        if (it->getName() == objectName)
        {
            return &*it;
        }
    }

    return nullptr;
}

std::vector<Purity::EntityState> Purity::EntityManager::getEntityStates() const
{
    std::vector<EntityState> states;

    states.reserve(mMovableObjectList.size());

    for (auto it = mMovableObjectList.begin(); it != mMovableObjectList.end(); ++it)
    {
        states.push_back(it->getState());
    }

    return states;
}

void Purity::EntityManager::initializeObjects()
{
    int numOfGroups = mTmxMap->GetNumObjectGroups();
   
    for (int groupNum = 0; groupNum < numOfGroups; groupNum++)
    {
        const Tmx::ObjectGroup* currentGroup;
        int numOfObjectsInGroup;

        currentGroup = mTmxMap->GetObjectGroup(groupNum);
        numOfObjectsInGroup = currentGroup->GetNumObjects();

        for (int objectNum = 0; objectNum < numOfObjectsInGroup; objectNum++)
        {
            const Tmx::Object* currentObject;

            currentObject = currentGroup->GetObject(objectNum);
            
            if (currentObject->GetType() == "Movable")
            {
                if (currentObject->GetProperties().GetSize() > 0)
                {
                    std::string p = currentObject->GetProperties().GetLiteralProperty("Texture");
                    const sf::Texture * t = mTextureManager.getTexture("scenes/init/" + p);
                    MovableEntity object(currentObject, mWorld, t);
                    mMovableObjectList.push_back(object);
                }
                else
                {
                    MovableEntity object(currentObject, mWorld, nullptr);
                    mMovableObjectList.push_back(object);
                }

            }
            else
            {
                Entity entity(currentObject, mWorld, nullptr);
                mObjectList.push_back(entity);

            }
            
        }
    }
}

Purity::MovableEntity* Purity::EntityManager::getMovableObjectById(const unsigned int id)
{
    for (auto it = mMovableObjectList.begin(); it != mMovableObjectList.end(); ++it)
    {
        if (it->getId() == id)
        {
            return &*it;
        }
    }

    return nullptr;
}

void Purity::EntityManager::updatePhysics()
{
    for (auto it = mObjectList.begin(); it != mObjectList.end(); it++)
    {
        it->update();
    }
    for (auto it = mMovableObjectList.begin(); it != mMovableObjectList.end(); it++)
    {
        it->update();
    }
}

void Purity::EntityManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto it = mObjectList.begin(); it != mObjectList.end(); it++)
    {
        target.draw(*it);
    }
    for (auto it = mMovableObjectList.begin(); it != mMovableObjectList.end(); it++)
    {
        target.draw(*it);
    }
}

luabind::scope Purity::EntityManager::luaBindings()
{
    return luabind::class_<EntityManager>("EntityManager")
        .def("getEntityByName", &EntityManager::getObjectByName)
        .def("getMovableEntityByName", &EntityManager::getMovableObjectByName)
    ;
}
