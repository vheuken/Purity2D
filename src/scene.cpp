#include "scene.h"

Purity::Scene::Scene(const boost::filesystem::path& sceneDir)
{
    boost::filesystem::path mapFilePath(sceneDir.string() + DEFAULT_MAP_FILENAME);
    
    mMap = std::unique_ptr<GameMap>(new GameMap(mapFilePath, sceneDir));
}

void Purity::Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*mMap, states);
}
