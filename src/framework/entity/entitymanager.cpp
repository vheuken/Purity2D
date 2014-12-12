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

    luabridge::setGlobal(LuaManager::getManager()->getState(), this, "GEntityManager");
}

Purity::Entity* const Purity::EntityManager::getEntityByName(const std::string& objectName)
{
    for (auto it = mEntityList.begin(); it != mEntityList.end(); ++it)
    {
        if (it->get()->getName() == objectName)
        {
            return it->get();
        }
    }

    return nullptr;
}

Purity::MovableEntity* const
Purity::EntityManager::getMovableEntityByName(const std::string& objectName)
{
    for (auto it = mMovableEntityList.begin(); it != mMovableEntityList.end(); ++it)
    {
        if (it->get()->getName() == objectName)
        {
            return it->get();
        }
    }

    return nullptr;
}

void Purity::EntityManager::destroyEntity(unsigned int id)
{
    auto deletionIt = mEntityList.end();

    for (auto it = mEntityList.begin(); it != mEntityList.end(); ++it)
    {
        if (it->get()->getId() == id)
        {
            deletionIt = it;
        }
    }

    if (deletionIt != mEntityList.end())
    {
        mEntityList.erase(deletionIt);
    }


    auto movableDeletionIt = mMovableEntityList.end();

    for (auto it = mMovableEntityList.begin(); it != mMovableEntityList.end(); ++it)
    {
        if (it->get()->getId() == id)
        {
            movableDeletionIt = it;
        }
    }

    if (movableDeletionIt != mMovableEntityList.end())
    {
        mMovableEntityList.erase(movableDeletionIt);
    }
}

std::vector<Purity::EntityState> Purity::EntityManager::getEntityStates() const
{
    std::vector<EntityState> states;

    states.reserve(mMovableEntityList.size());

    for (auto& entity : mMovableEntityList)
    {
        states.push_back(entity->getState());
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
                    Texture* t = mTextureManager.getTexture("scenes/init/" + p);
                    std::unique_ptr<MovableEntity> object(new MovableEntity(currentObject, mWorld, t));
                    mMovableEntityList.push_back(std::move(object));
                }
                else
                {
                    std::unique_ptr<MovableEntity> object(new MovableEntity(currentObject, mWorld, nullptr));
                    mMovableEntityList.push_back(std::move(object));
                }
            }
            else
            {
                std::unique_ptr<Entity> entity(new Entity(currentObject, mWorld, nullptr));
                mEntityList.push_back(std::move(entity));
            }
        }
    }
}

Purity::MovableEntity* const Purity::EntityManager::getMovableEntityById(const unsigned int id)
{
    for (auto it = mMovableEntityList.begin(); it != mMovableEntityList.end(); ++it)
    {
        if (it->get()->getId() == id)
        {
            return it->get();
        }
    }

    return nullptr;
}

void Purity::EntityManager::updatePhysics()
{
    for (auto& entity : mEntityList)
    {
        entity->update();
    }
    for (auto& entity : mMovableEntityList)
    {
        entity->update();
    }
}

void Purity::EntityManager::draw(Purity::RenderTarget& target) const
{
    for (auto& entity : mEntityList)
    {
        target.draw(*entity);
    }
    for (auto& entity : mMovableEntityList)
    {
        target.draw(*entity);
    }
}

void Purity::EntityManager::luaBindings(lua_State* state)
{
    luabridge::getGlobalNamespace(state)
        .beginNamespace("Purity")
        .beginClass<EntityManager>("EntityManager")
        .addFunction("destroyEntity", &EntityManager::destroyEntity)
        .addFunction("getEntityByName", &EntityManager::getEntityByName)
        .addFunction("getMovableEntityByName", &EntityManager::getMovableEntityByName)
        .endClass()
        .endNamespace();
}
