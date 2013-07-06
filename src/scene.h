#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>

namespace Purity
{

class Scene : public sf::Drawable
{
public:
    Scene();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

}

#endif // SCENE_H