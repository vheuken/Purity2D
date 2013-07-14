#ifndef LUA_MANAGER_H
#define LUA_MANAGER_H

#include <memory>
#include <lua.hpp>

namespace Purity
{
    class LuaManager
    {
    public:
        static LuaManager* getManager();

        lua_State* getState();

    private:
        LuaManager();

        lua_State* mLuaState;
    };
}

#endif // LUA_MANAGER_H