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
        Object(float x, float y, b2World* world);

        virtual void createBody(b2World* world);
        void setName(std::string name);
        std::string getName() const;
        void setX(float x);
        void setY(float y);
        float getX() const;
        float getY() const;

    protected:
        b2BodyDef mHitboxBodyDef;
        b2Body* mHitboxBody;     
        
        // visual representation of hitbox
        sf::RectangleShape mHitboxShape;

    private:
        float mPositionX;
        float mPositionY;

        std::string mName;

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };

}

#endif // OBJECT_H