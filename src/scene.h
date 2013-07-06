#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <SFML/Graphics.hpp>

#include "gamemap.h"

namespace Purity
{

class Scene : public sf::Drawable
{
public:
    Scene();

private:
    std::unique_ptr<GameMap> mMap;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

}

#endif // SCENE_H