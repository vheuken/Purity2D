#include "objectmanager.h"

Purity::ObjectManager::ObjectManager(const Tmx::Map* tmxMap, b2World* world)
{
    mTmxMap = tmxMap;
    mWorld = world;

    initializeObjects();
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
                mObjectList.push_back(object);
                
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
    for (int i = 0; i < mObjectList.size(); i++)
    {
        mObjectList.at(i).update();
    }
}

void Purity::ObjectManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (int i = 0; i < mObjectList.size(); i++)
    {
        target.draw(mObjectList.at(i));
    }
}