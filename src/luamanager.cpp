#include "luamanager.h"

Purity::LuaManager::LuaManager()
{
    mLuaState = luaL_newstate();

    luaL_openlibs(mLuaState);
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