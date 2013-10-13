#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <TmxParser/Tmx.h>
#include <luabind/luabind.hpp>

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

    class Object : public sf::Drawable
    {
    public:
        Object();
        Object(const Tmx::Object* object, b2World* world);

        virtual void createBody(b2World* world);
        void setName(std::string name);
        std::string getName() const;

        void setPosition(float x, float y);
        void setSize(float width, float height);
        
        float getX() const;
        float getY() const;

        void update();

        static luabind::scope luaBindings();

    protected:
        b2BodyDef mHitboxBodyDef;
        b2Body* mHitboxBody;     
        
        // visual representation of hitbox
        sf::RectangleShape mHitboxShape;

    private:
        float mPositionX;
        float mPositionY;
        float mWidthPixels;
        float mHeightPixels;

        std::string mName;

        void initializeHitboxShape();

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };

}

#endif // OBJECT_H