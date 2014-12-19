#include "tile.h"

Purity::Tile::Tile(int x, int y, int width, int height, Purity::Texture* texture, int id)
    : Entity()
    , mTileId(id)
{
    mAnimationFrame = id;
    mTexture = texture;

    mWidthPixels = width;
    mHeightPixels = height;

    setPosition(x * width, y * height);
}

void Purity::Tile::setTextureSubrect()
{
    if (mTexture != nullptr)
    {
        std::unique_ptr
            <SpriteSheet> spriteSheet(new SpriteSheet(mTexture, mWidthPixels, mHeightPixels));

        mSpriteSheet = std::move(spriteSheet);
    }
}

void Purity::Tile::initializePhysics(b2World* world)
{
    createBody(world);
    // setSize(mWidthPixels, mHeightPixels)

    initializeHitboxShape();
    setTextureSubrect();

    mHitboxBody->SetUserData(this);
}

void Purity::Tile::initializeStatic()
{
    initializeHitboxShape();
    setTextureSubrect();
}

void Purity::Tile::createBody(b2World* world)
{
    float32 posX, posY;
    b2BodyDef collisionTileBodyDef;
    b2EdgeShape collisionTileBox;

    posX = getPosition().x / PIXELS_PER_METER;
    posY = getPosition().y / PIXELS_PER_METER;

    // convert pixel coordinates to Box2D meters
    posX += mWidthPixels / PIXELS_PER_METER / 2;
    posY += mHeightPixels / PIXELS_PER_METER / 2;

    collisionTileBodyDef.position.Set(posX, posY);

    mHitboxBody = world->CreateBody(&collisionTileBodyDef);

    b2Vec2 lowerLeft(0 - (mWidthPixels / PIXELS_PER_METER / 2),
                     0 - (mHeightPixels / PIXELS_PER_METER / 2));
    b2Vec2 lowerRight(mWidthPixels / PIXELS_PER_METER / 2,
                      0 - (mHeightPixels / PIXELS_PER_METER / 2));
    b2Vec2 upperRight(mWidthPixels / PIXELS_PER_METER / 2,
                      mHeightPixels / PIXELS_PER_METER / 2);
    b2Vec2 upperLeft(0 - (mWidthPixels / PIXELS_PER_METER / 2),
                     mHeightPixels / PIXELS_PER_METER / 2);

    collisionTileBox.Set(lowerLeft, lowerRight);
    mHitboxBody->CreateFixture(&collisionTileBox, 0.0f);

    collisionTileBox.Set(upperRight, upperLeft);
    mHitboxBody->CreateFixture(&collisionTileBox, 0.0f);

    collisionTileBox.Set(upperLeft, lowerLeft);
    mHitboxBody->CreateFixture(&collisionTileBox, 0.0f);

    collisionTileBox.Set(lowerRight, upperRight);
    mHitboxBody->CreateFixture(&collisionTileBox, 0.0f);

    mHitboxBody->SetUserData(this);
}
