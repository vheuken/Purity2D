#include "scene.h"
#include "gamemap.h"

Purity::Scene::Scene()
{

}

void Purity::Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*mMap, states);
}