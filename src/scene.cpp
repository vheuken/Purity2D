#include "scene.h"

Purity::Scene::Scene(const boost::filesystem::path& sceneDir)
{
    boost::filesystem::path mapFilePath(sceneDir.string() + DEFAULT_MAP_FILENAME);

    mLuaEventHandlerFile = sceneDir.string() + DEFAULT_EVENT_HANDLER_FILENAME;
	mLuaPhysicsUpdateFile = sceneDir.string() + DEFAULT_ON_PHYSICS_UPDATE_SCRIPT;

    mTmxMap = std::unique_ptr<Tmx::Map>(new Tmx::Map);
    
    mTmxMap->ParseFile(mapFilePath.string());

    mMap = std::unique_ptr<GameMap>(new GameMap(mTmxMap.get(), sceneDir));
}

void Purity::Scene::initializePhysics(b2World * world)
{
    mMutex.lock();

    initializeTiles(world);
    mObjectManager = std::unique_ptr<ObjectManager>(new ObjectManager(mTmxMap.get(), world));

    mMutex.unlock();
}

std::string Purity::Scene::getLuaEventHandlerPath() const
{
    return mLuaEventHandlerFile.string();
}

std::string Purity::Scene::getLuaEventHandlerFunctionName() const
{
    return DEFAULT_EVENT_HANDLER_FUNCTION_NAME;
}

std::string Purity::Scene::getLuaPhysicsUpdatePath() const
{
    return mLuaPhysicsUpdateFile.string();
}


void Purity::Scene::initializeTiles(b2World * world)
{
    int layerCount;
    int tileWidth, tileHeight;

    layerCount = mTmxMap->GetNumLayers();
    tileWidth = mTmxMap->GetTileWidth();
    tileHeight = mTmxMap->GetTileHeight();

    b2BodyDef collisionTileBodyDef;
    b2Body * collisionTileBody;
    b2EdgeShape collisionTileBox;

    for (int layerNum = 0; layerNum < layerCount; layerNum++)
    {
        bool collidable;
        const Tmx::Layer * currentLayer;

        currentLayer = mTmxMap->GetLayer(layerNum);

        if (currentLayer->GetProperties().GetNumericProperty("Collidable"))
        {
            collidable = true;
        }
        else
        {
            collidable = false;
        }
        
        if (collidable)
        {
            for (int y = 0; y < mTmxMap->GetHeight(); y++)
            {
                for (int x = 0; x < mTmxMap->GetWidth(); x++)
                {
                    if (mTmxMap->GetLayer(layerNum)->GetTile(x, y).id != 0)
                    {
                        float32 posX, posY;

                        posX = x * mTmxMap->GetTileWidth()/PIXELS_PER_METER;
                        posY = y * mTmxMap->GetTileHeight()/PIXELS_PER_METER;

                        // convert Box2d coordinates to SFML compatible coordinates
                        posX += tileWidth/PIXELS_PER_METER/2;
                        posY += tileHeight/PIXELS_PER_METER/2;

                        collisionTileBodyDef.position.Set(posX, posY);

                        collisionTileBody = world->CreateBody(&collisionTileBodyDef);

                        b2Vec2 lowerLeft = b2Vec2(0 - (tileWidth/PIXELS_PER_METER/2), 0 - (tileHeight/PIXELS_PER_METER/2));
                        b2Vec2 lowerRight = b2Vec2(tileWidth/PIXELS_PER_METER/2, 0 - (tileHeight/PIXELS_PER_METER/2));
                        b2Vec2 upperRight = b2Vec2(tileWidth/PIXELS_PER_METER/2, tileHeight/PIXELS_PER_METER/2);
                        b2Vec2 upperLeft = b2Vec2(0 - (tileWidth/PIXELS_PER_METER/2), tileHeight/PIXELS_PER_METER/2);

                        collisionTileBox.Set(lowerLeft, lowerRight);
                        collisionTileBody->CreateFixture(&collisionTileBox, 0.0f);

                        collisionTileBox.Set(upperRight, upperLeft);
                        collisionTileBody->CreateFixture(&collisionTileBox, 0.0f);

                        collisionTileBox.Set(upperLeft, lowerLeft);
                        collisionTileBody->CreateFixture(&collisionTileBox, 0.0f);

                        collisionTileBox.Set(lowerRight, upperRight);
                        collisionTileBody->CreateFixture(&collisionTileBox, 0.0f);

                        int tilesetId = mTmxMap->GetLayer(layerNum)->GetTile(x, y).tilesetId;
                        int tileId = mTmxMap->GetLayer(layerNum)->GetTile(x, y).id;
                        int tilesetFirstGid = mTmxMap->GetTileset(tilesetId)->GetFirstGid();
                        std::map<std::string, std::string> tilePropertyMap;

                        collisionTileBody->SetUserData(new std::string("Tile"));

                        mTileBodyList.push_back(collisionTileBody);

                    }
                }
            }
        }
    }
}

void Purity::Scene::initializeObjects(b2World* world)
{

}

void Purity::Scene::updatePhysics()
{    
    mMutex.lock();

    mObjectManager->updatePhysics();

    mMutex.unlock();
}

void Purity::Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    mMutex.lock();

    target.draw(*mMap, states);

    target.draw(*mObjectManager, states);

    mMutex.unlock();
}
