#include "object.h"

Purity::Object::Object(float x, float y, b2World* world)
{
    mHitboxBodyDef.type = b2_dynamicBody;

    mHitboxBodyDef.position.Set(14, 3);

    createBody(world);
    setX(x);
    setY(y);
    initializeHitboxShape();
}

void Purity::Object::setX(float x)
{
    this->mPositionX = x;
    b2Vec2 pos;
    pos.Set(x, getY());

    mHitboxBody->SetTransform(pos, mHitboxBody->GetAngle());
}

void Purity::Object::setY(float y)
{
    this->mPositionY = y;
    b2Vec2 pos;
    pos.Set(getX(), y);

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
        b2PolygonShape hitboxBox;

        hitboxBox.SetAsBox(DEFAULT_HITBOX_WIDTH_METERS/2, DEFAULT_HITBOX_HEIGHT_METERS/2);
        
        b2FixtureDef hitboxFixtureDef;
        hitboxFixtureDef.shape = &hitboxBox;
        
        hitboxFixtureDef.density = 0.0f;
        
        mHitboxBody->CreateFixture(&hitboxFixtureDef);

        // sensor text
        b2FixtureDef ledgeSensorBottomDef, ledgeSensorTopDef;
        b2PolygonShape ledgeSensorBottomShape, ledgeSensorTopShape;
        b2Vec2 vertices[4];
        int verticeCount = 4;



        vertices[0].Set(-DEFAULT_HITBOX_WIDTH_METERS*1.25,   DEFAULT_HITBOX_HEIGHT_METERS/-2);
        vertices[1].Set(DEFAULT_HITBOX_WIDTH_METERS*1.25,  DEFAULT_HITBOX_HEIGHT_METERS/-2);
        vertices[2].Set(DEFAULT_HITBOX_WIDTH_METERS*1.25, 0);
        vertices[3].Set(-DEFAULT_HITBOX_WIDTH_METERS*1.25,  0);


        ledgeSensorBottomShape.Set(vertices, verticeCount);
        
        ledgeSensorBottomDef.isSensor = true;
        ledgeSensorBottomDef.userData = new std::string("LedgeSensorBottom");
        ledgeSensorBottomDef.shape = &ledgeSensorBottomShape;
        
        vertices[0].Set(-DEFAULT_HITBOX_WIDTH_METERS*1.25,   -DEFAULT_HITBOX_HEIGHT_METERS);
        vertices[1].Set(DEFAULT_HITBOX_WIDTH_METERS*1.25,  -DEFAULT_HITBOX_HEIGHT_METERS);
        vertices[2].Set(DEFAULT_HITBOX_WIDTH_METERS*1.25, 0);
        vertices[3].Set(-DEFAULT_HITBOX_WIDTH_METERS*1.25,  0);
        
        ledgeSensorTopShape.Set(vertices, verticeCount);

        ledgeSensorTopDef.isSensor = true;
        ledgeSensorTopDef.userData = new std::string("LedgeSensorTop");
        ledgeSensorTopDef.shape = &ledgeSensorTopShape;

        mHitboxBody->CreateFixture(&ledgeSensorBottomDef);
        mHitboxBody->CreateFixture(&ledgeSensorTopDef);

        mHitboxBody->SetUserData( this );

}

void Purity::Object::initializeHitboxShape()
{
    mHitboxShape.setPosition(0, 0);
    sf::Vector2f hitboxSize(DEFAULT_HITBOX_WIDTH_PIXELS, DEFAULT_HITBOX_HEIGHT_PIXELS);
    mHitboxShape.setSize(hitboxSize);
    mHitboxShape.setOutlineColor(DEFAULT_HITBOX_OUTLINE_COLOR);
    mHitboxShape.setOutlineThickness(DEFAULT_HITBOX_OUTLINE_THICKNESS);
    mHitboxShape.setFillColor(DEFAULT_HITBOX_FILL_COLOR);
}

void Purity::Object::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mHitboxShape);
}