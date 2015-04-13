#include "gamemap.h"

#include <Tmx.h>

Purity::GameMap::GameMap(const Tmx::Map* tmxMap,
                         b2World* world,
                         const std::string& sceneDir,
                         EntityManager* entityManager)
    : mSceneDir(sceneDir)
    , mTmxMap(tmxMap)
    , mWorld(world)
    , mTextureManager(new TextureManager())
    , mEntityManager(entityManager)
{
    processLayers();
}

Purity::Layer* Purity::GameMap::getLayer(int layerNum) const
{
    return mLayersList[layerNum].get();
}

void Purity::GameMap::processLayers()
{
    const std::vector<Tmx::Layer*, std::allocator<Tmx::Layer*>> tmxLayers = mTmxMap->GetLayers();

    for (auto it = tmxLayers.begin(); it != tmxLayers.end(); ++it)
    {
        std::unique_ptr<Layer> layer(
            new Layer(mTmxMap, *it, mWorld, mTextureManager.get(), mSceneDir, mEntityManager));

        mLayersList.push_back(std::move(layer));
    }
}

void Purity::GameMap::draw(Purity::RenderTarget& target) const
{
    for (auto it = mLayersList.begin(); it != mLayersList.end(); ++it)
    {
        target.draw(*it->get());
    }
}
