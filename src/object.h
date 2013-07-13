#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

namespace Purity
{
    class Object : public sf::Drawable
    {
    public:
        virtual void createBody(b2World* world);
        void setName(std::string name);
        std::string getName() const;
        void setX(float x);
        void setY(float y);
        float getX() const;
        float getY() const;

    protected:
        b2BodyDef hitboxBodyDef;
        b2Body* hitboxBody;     
        
        // visual representation of hitbox
        sf::RectangleShape visibleHitbox;

    private:
        int positionX;
        int positionY;

        std::string name;

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };

}

#endif // OBJECT_H