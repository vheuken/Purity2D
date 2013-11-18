#include "tile.h"

Purity::Tile::Tile(int x, int y, int width, int height, const sf::Sprite& tileSprite)
{
    mTileSprite = tileSprite;
    
    setPosition(x, y);

    mWidthPixels = width;
    mHeightPixels = height;
}

void Purity::Tile::initializePhysics(b2World * world)
{
    createBody(world);
}

void Purity::Tile::createBody(b2World* world)
{
    float32 posX, posY;
    b2BodyDef collisionTileBodyDef;
    b2EdgeShape collisionTileBox;

    posX = getPosition().x * mWidthPixels  / PIXELS_PER_METER;
    posY = getPosition().y * mHeightPixels / PIXELS_PER_METER;

    // convert SFML coordinates to Box2D compatible coordinates
    posX += mWidthPixels  / PIXELS_PER_METER / 2;
    posY += mHeightPixels / PIXELS_PER_METER / 2;

    collisionTileBodyDef.position.Set(posX, posY);

    mHitboxBody = world->CreateBody(&collisionTileBodyDef);
    
    b2Vec2 lowerLeft = b2Vec2(0 - (mWidthPixels/PIXELS_PER_METER/2), 0 - (mHeightPixels/PIXELS_PER_METER/2));
    b2Vec2 lowerRight = b2Vec2(mWidthPixels/PIXELS_PER_METER/2, 0 - (mHeightPixels/PIXELS_PER_METER/2));
    b2Vec2 upperRight = b2Vec2(mWidthPixels/PIXELS_PER_METER/2, mHeightPixels/PIXELS_PER_METER/2);
    b2Vec2 upperLeft = b2Vec2(0 - (mWidthPixels/PIXELS_PER_METER/2), mHeightPixels/PIXELS_PER_METER/2);

    collisionTileBox.Set(lowerLeft, lowerRight);
    mHitboxBody->CreateFixture(&collisionTileBox, 0.0f);
    
    collisionTileBox.Set(upperRight, upperLeft);
    mHitboxBody->CreateFixture(&collisionTileBox, 0.0f);
    
    collisionTileBox.Set(upperLeft, lowerLeft);
    mHitboxBody->CreateFixture(&collisionTileBox, 0.0f);
    
    collisionTileBox.Set(lowerRight, upperRight);
    mHitboxBody->CreateFixture(&collisionTileBox, 0.0f);
    

    mHitboxBody->SetUserData(new std::string("Tile"));
}

void Purity::Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::View view = target.getView();
    
    if ( isInView(view) )
    {
        target.draw(mTileSprite);
    }
}

bool Purity::Tile::isInView(const sf::View& view) const
{
    sf::Vector2f viewPos, viewSize;

    viewPos = view.getCenter();
    viewSize = view.getSize();
    viewPos.x -= view.getSize().x/2;
    viewPos.y -= view.getSize().y/2;

    sf::FloatRect viewRect(viewPos, viewSize);
    sf::FloatRect tileBounds = mTileSprite.getGlobalBounds();

    return viewRect.intersects(tileBounds);
}