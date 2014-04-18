#include "scene.h"

Purity::Scene::Scene(const std::string& sceneDir)
{
    std::string mapFilePath(sceneDir + DEFAULT_MAP_FILENAME);

    mLuaEventHandlerFile = sceneDir + DEFAULT_EVENT_HANDLER_FILENAME;
    mLuaPhysicsUpdateFile = sceneDir + DEFAULT_ON_PHYSICS_UPDATE_SCRIPT;

    mTmxMap = std::unique_ptr<Tmx::Map>(new Tmx::Map);

    mTmxMap->ParseFile(mapFilePath);

    mMap = std::unique_ptr<GameMap>(new GameMap(mTmxMap.get(), sceneDir));
}

void Purity::Scene::initializePhysics(b2World * world)
{
    mMutex.lock();

    initializeTiles(world);
    mObjectManager = std::unique_ptr<EntityManager>(new EntityManager(mTmxMap.get(), world));

    mMutex.unlock();
}

void Purity::Scene::setEntityState(const EntityState& state)
{
    mObjectManager->getMovableEntityById(state.entityId)->setBodyPosition(state.position.x, state.position.y);
}

std::vector<Purity::EntityState> Purity::Scene::getEntityStates() const
{
    return mObjectManager->getEntityStates();
}

std::string Purity::Scene::getLuaEventHandlerPath() const
{
    return mLuaEventHandlerFile;
}

std::string Purity::Scene::getLuaEventHandlerFunctionName() const
{
    return DEFAULT_EVENT_HANDLER_FUNCTION_NAME;
}

std::string Purity::Scene::getLuaPhysicsUpdatePath() const
{
    return mLuaPhysicsUpdateFile;
}


void Purity::Scene::initializeTiles(b2World * world)
{
    mMap->initializeTilePhysics(world);
}

void Purity::Scene::initializeObjects(b2World* world)
{

}

void Purity::Scene::updatePhysics()
{
    mMutex.lock();

    mObjectManager->updatePhysics();

    mMutex.unlock();
}

void Purity::Scene::draw(Purity::RenderTarget& target) const
{
    mMutex.lock();

    target.draw(*mMap);

    target.draw(*mObjectManager);

    mMutex.unlock();
}
