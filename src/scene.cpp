#include "scene.h"

Purity::Scene::Scene(const boost::filesystem::path& sceneDir)
{
    boost::filesystem::path mapFilePath(sceneDir.string() + DEFAULT_MAP_FILENAME);

    mTmxMap = std::unique_ptr<Tmx::Map>(new Tmx::Map);
    
    mTmxMap->ParseFile(mapFilePath.string());

    mMap = std::unique_ptr<GameMap>(new GameMap(mTmxMap.get(), sceneDir));
}

void Purity::Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*mMap, states);
}
