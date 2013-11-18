#include "entity.h"

#include <luabind/luabind.hpp>
#include <TmxParser/Tmx.h>

Purity::Entity::Entity()
{
}

Purity::Entity::Entity(const Tmx::Object* object, b2World* world)
{
    float x = object->GetX() / PIXELS_PER_METER;
    float y = object->GetY() / PIXELS_PER_METER;
    float width = (float)object->GetWidth();
    float height = (float)object->GetHeight();
    
    mName = object->GetName();

    createBody(world);
    setPosition(x, y);
    setSize(width, height);
}

void Purity::Entity::setPosition(float x, float y)
{
    this->mPositionX = x;
    this->mPositionY = y;

    b2Vec2 pos;
    pos.Set(x, y);

    mHitboxBody->SetTransform(pos, mHitboxBody->GetAngle());
}

float Purity::Entity::getX() const
{
    return mPositionX;
}

float Purity::Entity::getY() const
{
    return mPositionY;
}

std::string Purity::Entity::getName() const
{
    return mName;
}

void Purity::Entity::setSize(float width, float height)
{
    mWidthPixels = width;
    mHeightPixels = height;

    b2PolygonShape hitboxBox;
    b2FixtureDef hitboxFixtureDef;

    hitboxBox.SetAsBox(mWidthPixels / PIXELS_PER_METER /2, mHeightPixels / PIXELS_PER_METER /2);
        
    hitboxFixtureDef.shape = &hitboxBox;
        
    hitboxFixtureDef.density = 0.0f;
        
    mHitboxBody->CreateFixture(&hitboxFixtureDef);

    mHitboxBody->SetUserData( this );
    
    initializeHitboxShape();
}

void Purity::Entity::update()
{
    mPositionX = (mHitboxBody->GetPosition().x * PIXELS_PER_METER) - (mHitboxShape.getSize().x/2);
    mPositionY = (mHitboxBody->GetPosition().y * PIXELS_PER_METER) - (mHitboxShape.getSize().y/2);

    mHitboxShape.setPosition(mPositionX, mPositionY);
}

void Purity::Entity::createBody(b2World* world)
{
    mHitboxBody = world->CreateBody(&mHitboxBodyDef);
}

void Purity::Entity::initializeHitboxShape()
{
    sf::Vector2f hitboxSize(mWidthPixels, mHeightPixels);
    mHitboxShape.setSize(hitboxSize);
    mHitboxShape.setOutlineColor(DEFAULT_HITBOX_OUTLINE_COLOR);
    mHitboxShape.setOutlineThickness(DEFAULT_HITBOX_OUTLINE_THICKNESS);
    mHitboxShape.setFillColor(DEFAULT_HITBOX_FILL_COLOR);
}

void Purity::Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mHitboxShape);
}

luabind::scope Purity::Entity::luaBindings()
{
    return luabind::class_<Entity>("Object")
        .def("getName", &Entity::getName)
    ;
}