#include "entitymanager.h"

#include <LuaBridge.h>
#include <TmxParser/Tmx.h>

#include "../graphics/texture.h"

#include "../../engine/luamanager.h"

Purity::EntityManager::EntityManager(const Tmx::Map* tmxMap, b2World* world)
{
    mTmxMap = tmxMap;
    mWorld = world;

    initializeObjects();

    //luabind::globals(LuaManager::getManager()->getState())["GEntityManager"] = this;
    luabridge::setGlobal(LuaManager::getManager()->getState(), this, "GEntityManager");
}

Purity::Entity* const Purity::EntityManager::getEntityByName(const std::string& objectName)
{
    for (auto it = mEntityList.begin(); it != mEntityList.end(); ++it)
    {
        if (it->getName() == objectName)
        {
            return &*it;
        }
    }

    return nullptr;
}

Purity::MovableEntity* const Purity::EntityManager::getMovableEntityByName(const std::string& objectName)
{

    for (auto it = mMovableEntityList.begin(); it != mMovableEntityList.end(); ++it)
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

    states.reserve(mMovableEntityList.size());

    for (auto it = mMovableEntityList.begin(); it != mMovableEntityList.end(); ++it)
    {
        states.push_back(it->getState());
    }

    return states;
}

void Purity::EntityManager::initializeObjects()
{
    int numOfGroups = mTmxMap->GetNumObjectGroups();

    for (int groupNum = 0; groupNum < numOfGroups; ++groupNum)
    {
        const Tmx::ObjectGroup* currentGroup;
        int numOfObjectsInGroup;

        currentGroup = mTmxMap->GetObjectGroup(groupNum);
        numOfObjectsInGroup = currentGroup->GetNumObjects();

        for (int objectNum = 0; objectNum < numOfObjectsInGroup; ++objectNum)
        {
            const Tmx::Object* currentObject;

            currentObject = currentGroup->GetObject(objectNum);

            if (currentObject->GetType() == "Movable")
            {
                if (currentObject->GetProperties().GetSize() > 0)
                {
                    std::string p = currentObject->GetProperties().GetLiteralProperty("Texture");
                    Texture * t = mTextureManager.getTexture("scenes/init/" + p);
                    MovableEntity object(currentObject, mWorld, t);
                    mMovableEntityList.push_back(std::move(object));
                }
                else
                {
                    MovableEntity object(currentObject, mWorld, nullptr);
                    mMovableEntityList.push_back(std::move(object));
                }

            }
            else
            {
                Entity entity(currentObject, mWorld, nullptr);
                mEntityList.push_back(std::move(entity));

            }

        }
    }
}

Purity::MovableEntity* const Purity::EntityManager::getMovableEntityById(const unsigned int id)
{
    for (auto it = mMovableEntityList.begin(); it != mMovableEntityList.end(); ++it)
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
    for (auto it = mEntityList.begin(); it != mEntityList.end(); ++it)
    {
        it->update();
    }
    for (auto it = mMovableEntityList.begin(); it != mMovableEntityList.end(); ++it)
    {
        it->update();
    }
}

void Purity::EntityManager::draw(Purity::RenderTarget& target) const
{
    for (auto it = mEntityList.begin(); it != mEntityList.end(); ++it)
    {
        target.draw(*it);
    }
    for (auto it = mMovableEntityList.begin(); it != mMovableEntityList.end(); ++it)
    {
        target.draw(*it);
    }
}


void Purity::EntityManager::luaBindings(lua_State* state)
{
    luabridge::getGlobalNamespace(state)
            .beginNamespace("Purity")
                .beginClass <EntityManager> ("EntityManager")
                    .addFunction("getEntityByName", &EntityManager::getEntityByName)
                    .addFunction("getMovableEntityByName", &EntityManager::getMovableEntityByName)
                .endClass()
            .endNamespace();
}

