#ifndef LUA_MANAGER_H
#define LUA_MANAGER_H

#include <string>

struct lua_State;

namespace Purity
{
class LuaManager
{
public:
    ~LuaManager();
    static LuaManager* getManager();

    lua_State* getState();

    void doFile(const std::string& luaFileName);
    void loadFile(const std::string& luaFileName);

private:
    LuaManager();

    lua_State* mLuaState;

    void initializeBindings();
    void initializeMiscBindings();
};
}

#endif // LUA_MANAGER_H
