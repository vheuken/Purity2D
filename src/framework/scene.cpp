#include "scene.h"

Purity::Scene::Scene(const std::string& sceneDir, b2World* world)
    : mWorld(world)
{
    std::string mapFilePath(sceneDir + DEFAULT_MAP_FILENAME);

    mLuaEventHandlerFile = sceneDir + DEFAULT_EVENT_HANDLER_FILENAME;
    mLuaPhysicsUpdateFile = sceneDir + DEFAULT_MAIN_SCRIPT;

    mTmxMap = std::unique_ptr<Tmx::Map>(new Tmx::Map);

    mTmxMap->ParseFile(mapFilePath);

    mMap = std::unique_ptr<GameMap>(new GameMap(mTmxMap.get(), mWorld, sceneDir, mEntityManager.get()));
}

Purity::GameMap* Purity::Scene::getMap() const
{
    return mMap.get();
}

void Purity::Scene::initializePhysics(b2World* world)
{
    //mMutex.lock();

    mEntityManager = std::unique_ptr<EntityManager>(new EntityManager(mTmxMap.get(), world));

    //mMutex.unlock();
}

void Purity::Scene::setEntityState(const EntityState& state)
{
    mEntityManager->getMovableEntityById(state.entityId)
        ->setBodyPosition(state.position.x, state.position.y);
}

std::vector<Purity::EntityState> Purity::Scene::getEntityStates() const
{
    return mEntityManager->getEntityStates();
}

std::string Purity::Scene::getLuaEventHandlerPath() const
{
    return mLuaEventHandlerFile;
}

std::string Purity::Scene::getLuaEventHandlerFunctionName() const
{
    return DEFAULT_EVENT_HANDLER_FUNCTION_NAME;
}

std::string Purity::Scene::getLuaMainPath() const
{
    return mLuaPhysicsUpdateFile;
}

void Purity::Scene::updatePhysics()
{
    mMutex.lock();

    mEntityManager->updatePhysics();

    mMutex.unlock();
}

void Purity::Scene::draw(Purity::RenderTarget& target) const
{
    mMutex.lock();

    target.draw(*mMap);

    target.draw(*mEntityManager);

    mMutex.unlock();
}
