#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <memory>
#include <Box2D/Box2D.h>
#include <lua.hpp>

#include "entitystate.h"
#include "../graphics/drawable.h"
#include "../graphics/vertexarray.h"
#include "../graphics/texture.h"
#include "../graphics/rect.h"
#include "../graphics/transformable.h"
#include "../spritesheet.h"

#include "../system/configuration.h"


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
    const float32 PIXELS_PER_METER = 30.f;//= Configuration::getInstance()->getReal("physics", "pixels_per_meter", 30.0);
    const float32 DEFAULT_HITBOX_WIDTH_METERS = 0.5;
    const float32 DEFAULT_HITBOX_HEIGHT_METERS = 1.5;

    const float32 DEFAULT_HITBOX_WIDTH_PIXELS  = PIXELS_PER_METER * DEFAULT_HITBOX_WIDTH_METERS;
    const float32 DEFAULT_HITBOX_HEIGHT_PIXELS = PIXELS_PER_METER * DEFAULT_HITBOX_HEIGHT_METERS;

    const float DEFAULT_HITBOX_OUTLINE_THICKNESS = 2.0;

    class Entity : public Drawable, protected Transformable
    {
    public:
        Entity();
        Entity(const Tmx::Object* object, b2World* world, Texture * texture);

        virtual void createBody(b2World* world);
        void setName(std::string name);
        std::string getName() const;

        void setBodyPosition(float x, float y);
        void setSize(float width, float height);

        float getX() const;
        float getY() const;

        const unsigned int getId() const;

        EntityState getState() const;

        virtual void update();

        static void luaBindings(lua_State* state);

    protected:
        b2BodyDef mHitboxBodyDef;
        b2Body* mHitboxBody;
        Rect mHitboxRect;

        Texture* mTexture;
        std::unique_ptr<SpriteSheet> mSpriteSheet;
        unsigned short mAnimationFrame;

        float mWidthPixels;
        float mHeightPixels;

        void initializeHitboxShape();

    private:
        static unsigned int sNumOfEntities;
        const unsigned int mId;
        std::string mName;

        EntityState mState;

        void updateState();

        virtual void draw(RenderTarget& target) const;
    };

}

#endif // ENTITY_H
