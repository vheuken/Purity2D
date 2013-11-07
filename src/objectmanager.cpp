#include "objectmanager.h"

#include <luabind/luabind.hpp>
#include <TmxParser/Tmx.h>
#include "luamanager.h"

Purity::ObjectManager::ObjectManager(const Tmx::Map* tmxMap, b2World* world)
{
    mTmxMap = tmxMap;
    mWorld = world;

    initializeObjects();

    luabind::globals(LuaManager::getManager()->getState())["GObjectManager"] = this;
}

const Purity::Object* Purity::ObjectManager::getObjectByName(const std::string& objectName)
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

Purity::MovableObject* Purity::ObjectManager::getMovableObjectByName(const std::string& objectName)
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

void Purity::ObjectManager::initializeObjects()
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
                MovableObject object(currentObject, mWorld);
                mMovableObjectList.push_back(object);
            }
            else
            {
                Object object(currentObject, mWorld);
                mObjectList.push_back(object);

            }
            
        }
    }
}

void Purity::ObjectManager::updatePhysics()
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

void Purity::ObjectManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
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

luabind::scope Purity::ObjectManager::luaBindings()
{
    return luabind::class_<ObjectManager>("ObjectManager")
        .def("getObjectByName", &ObjectManager::getObjectByName)
        .def("getMovableObjectByName", &ObjectManager::getMovableObjectByName)
    ;
}