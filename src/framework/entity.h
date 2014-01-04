#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "entitystate.h"

namespace luabind
{
    struct scope;
}

namespace Tmx
{   
    class Object;
}

namespace Purity
{
    const float32 PIXELS_PER_METER = 30.0f;
    const float32 DEFAULT_HITBOX_WIDTH_METERS = 0.5;
    const float32 DEFAULT_HITBOX_HEIGHT_METERS = 1.5;

    const float32 DEFAULT_HITBOX_WIDTH_PIXELS  = PIXELS_PER_METER * DEFAULT_HITBOX_WIDTH_METERS; 
    const float32 DEFAULT_HITBOX_HEIGHT_PIXELS = PIXELS_PER_METER * DEFAULT_HITBOX_HEIGHT_METERS;


    const float DEFAULT_HITBOX_OUTLINE_THICKNESS = 2.0;
    const sf::Color DEFAULT_HITBOX_OUTLINE_COLOR = sf::Color::Yellow;
    const sf::Color DEFAULT_HITBOX_FILL_COLOR = sf::Color::Transparent;

    class Entity : public sf::Drawable, public sf::Transformable
    {
    public:
        Entity();
        Entity(const Tmx::Object* object, b2World* world, const sf::Texture * texture);

        virtual void createBody(b2World* world);
        void setName(std::string name);
        std::string getName() const;

        void setBodyPosition(float x, float y);
        void setSize(float width, float height);
        
        float getX() const;
        float getY() const;

        EntityState getState() const;

        virtual void update();

        static luabind::scope luaBindings();

    protected:
        b2BodyDef mHitboxBodyDef;
        b2Body* mHitboxBody;     

        sf::VertexArray mVertexArray;
        const sf::Texture * mTexture;

        float mWidthPixels;
        float mHeightPixels;

        void initializeHitboxShape();

    private:
        std::string mName;

        EntityState mState;

        void initializeTextureCoords();

        bool isInView(const sf::View& view) const;

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };

}

#endif // ENTITY_H
