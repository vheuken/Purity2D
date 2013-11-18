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
    setBodyPosition(x, y);
    setSize(width, height);
}

void Purity::Entity::setBodyPosition(float x, float y)
{
    b2Vec2 pos;
    pos.Set(x, y);

    mHitboxBody->SetTransform(pos, mHitboxBody->GetAngle());
}

float Purity::Entity::getX() const
{
    return getPosition().x;
}

float Purity::Entity::getY() const
{
    return getPosition().y;
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
    float x = (mHitboxBody->GetPosition().x * PIXELS_PER_METER) - (mWidthPixels/2);
    float y = (mHitboxBody->GetPosition().y * PIXELS_PER_METER) - (mHeightPixels/2);

    setPosition(x, y);
}

void Purity::Entity::createBody(b2World* world)
{
    mHitboxBody = world->CreateBody(&mHitboxBodyDef);
}

void Purity::Entity::initializeHitboxShape()
{
    mVertexArray.setPrimitiveType(sf::Quads);

    mVertexArray.append(sf::Vector2f(0, 0));
    mVertexArray.append(sf::Vector2f(mWidthPixels, 0));
    mVertexArray.append(sf::Vector2f(mWidthPixels, mHeightPixels));
    mVertexArray.append(sf::Vector2f(0, mHeightPixels));
}

void Purity::Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mVertexArray, states);
}

luabind::scope Purity::Entity::luaBindings()
{
    return luabind::class_<Entity>("Object")
        .def("getName", &Entity::getName)
    ;
}