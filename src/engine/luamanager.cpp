#include "luamanager.h"

#include <lua.hpp>
#include <LuaBridge.h>
#include <SDL.h>
#include "../framework/entity/entity.h"
#include "../framework/entity/movableentity.h"
#include "../framework/entity/entitymanager.h"
#include "../framework/system/event.h"
#include "engine.h"

Purity::LuaManager::LuaManager()
{
    mLuaState = luaL_newstate();

    luaL_openlibs(mLuaState);

    initializeBindings();
}

Purity::LuaManager::~LuaManager()
{
    lua_close(mLuaState);
}

Purity::LuaManager* Purity::LuaManager::getManager()
{
    static LuaManager manager;
    return &manager;
}

lua_State* Purity::LuaManager::getState()
{
    return mLuaState;
}

void Purity::LuaManager::doFile(const std::string& luaFileName)
{
    SDL_RWops* file = SDL_RWFromFile(luaFileName.c_str(), "rb");

    int fileSize = file->size(file);
    char* fileContents = new char[fileSize + 1];

    file->read(file, fileContents, 1, fileSize);
    fileContents[fileSize] = '\0';

    file->close(file);

    luaL_dostring(mLuaState, fileContents);

    delete [] fileContents;
}

void Purity::LuaManager::loadFile(const std::string& luaFileName)
{
    luaL_loadfile(mLuaState, luaFileName.c_str());
}

void Purity::LuaManager::initializeBindings()
{
    NetworkSystem::luaBindings(mLuaState);
    EntityManager::luaBindings(mLuaState);
    Entity::luaBindings(mLuaState);
    MovableEntity::luaBindings(mLuaState);
    initializeSFMLBindings();
}

void Purity::LuaManager::initializeMiscBindings()
{
    luabridge::getGlobalNamespace(mLuaState)
        .beginNamespace("Purity")
            .beginClass<Event>("Event")
                .addData("type", &Event::type, false)
                .addData("keyEvent", &Event::keyEvent, false)
            .endClass()
            .beginClass<Event::KeyEvent>("KeyEvent")
                .addData("code", &Event::KeyEvent::code, false)
            .endClass()
        .endNamespace();
}
