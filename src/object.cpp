#include "object.h"

Purity::Object::Object(float x, float y, b2World* world)
{
    mHitboxBodyDef.type = b2_dynamicBody;

    createBody(world);
    setPosition(x, y);
}

void Purity::Object::setPosition(float x, float y)
{
    this->mPositionX = x;
    this->mPositionY = y;

    b2Vec2 pos;
    pos.Set(x, y);

    mHitboxBody->SetTransform(pos, mHitboxBody->GetAngle());
}
float Purity::Object::getX() const
{
    return mPositionX;
}

float Purity::Object::getY() const
{
    return mPositionY;
}

void Purity::Object::setSize(float width, float height)
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

void Purity::Object::update()
{
    float posX, posY;

    posX = (mHitboxBody->GetPosition().x * PIXELS_PER_METER) - (mHitboxShape.getSize().x/2);
    posY = (mHitboxBody->GetPosition().y * PIXELS_PER_METER) - (mHitboxShape.getSize().y/2);

    mHitboxShape.setPosition(posX, posY);
}

void Purity::Object::createBody(b2World* world)
{
    mHitboxBody = world->CreateBody(&mHitboxBodyDef);
}

void Purity::Object::initializeHitboxShape()
{
    mHitboxShape.setPosition(100, 100);
    sf::Vector2f hitboxSize(mWidthPixels, mHeightPixels);
    mHitboxShape.setSize(hitboxSize);
    mHitboxShape.setOutlineColor(DEFAULT_HITBOX_OUTLINE_COLOR);
    mHitboxShape.setOutlineThickness(DEFAULT_HITBOX_OUTLINE_THICKNESS);
    mHitboxShape.setFillColor(DEFAULT_HITBOX_FILL_COLOR);
}

void Purity::Object::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mHitboxShape);
}