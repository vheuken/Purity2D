#include "tile.h"

Purity::Tile::Tile(int x, int y, int width, int height, const sf::Sprite& tileSprite)
{
    mTileSprite = tileSprite;
    mTilePosX = x;
    mTilePosY = y;
    mTileWidth = width;
    mTileHeight = height;
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

    posX = mTilePosX * mTileWidth  / PIXELS_PER_METER;
    posY = mTilePosY * mTileHeight / PIXELS_PER_METER;

    // convert SFML coordinates to Box2D compatible coordinates
    posX += mTileWidth  / PIXELS_PER_METER / 2;
    posY += mTileHeight / PIXELS_PER_METER / 2;

    collisionTileBodyDef.position.Set(posX, posY);

    mHitboxBody = world->CreateBody(&collisionTileBodyDef);
    
    b2Vec2 lowerLeft = b2Vec2(0 - (mTileWidth/PIXELS_PER_METER/2), 0 - (mTileHeight/PIXELS_PER_METER/2));
    b2Vec2 lowerRight = b2Vec2(mTileWidth/PIXELS_PER_METER/2, 0 - (mTileHeight/PIXELS_PER_METER/2));
    b2Vec2 upperRight = b2Vec2(mTileWidth/PIXELS_PER_METER/2, mTileHeight/PIXELS_PER_METER/2);
    b2Vec2 upperLeft = b2Vec2(0 - (mTileWidth/PIXELS_PER_METER/2), mTileHeight/PIXELS_PER_METER/2);

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

void Purity::Tile::update()
{

}

void Purity::Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::View view = target.getView();

    target.draw(mTileSprite);
}