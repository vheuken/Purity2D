#include "luamanager.h"

#include <lua.hpp>
#include <LuaBridge.h>
#include <SDL.h>
#include "../framework/entity/entity.h"
#include "../framework/entity/movableentity.h"
#include "../framework/entity/entitymanager.h"
#include "../framework/system/event.h"
#include "../framework/system/timer.h"
#include "../framework/system/actionmanager.h"
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
    Timer::luaBindings(mLuaState);
    initializeMiscBindings();
}

void Purity::LuaManager::initializeMiscBindings()
{
    luabridge::getGlobalNamespace(mLuaState)
        .beginNamespace("Purity")
            .beginClass<Event>("Event")
                .addData("type", &Event::type, false)
                .addData("keyEvent", &Event::keyEvent, false)
                .addData("touchEvent", &Event::touchEvent, false)
            .endClass()
            .beginClass<Event::KeyEvent>("KeyEvent")
                .addData("code", &Event::KeyEvent::code, false)
            .endClass()
            .beginClass<Event::TouchEvent>("TouchEvent")
                .addData("x", &Event::TouchEvent::x, false)
                .addData("y", &Event::TouchEvent::y, false)
                .addData("dx", &Event::TouchEvent::dx, false)
                .addData("dy", &Event::TouchEvent::dy, false)
                .addData("pressure", &Event::TouchEvent::pressure, false)
            .endClass()
            .beginNamespace("EventType")
                .addVariable("KeyPressed", new int(SDL_KEYDOWN))
                .addVariable("KeyReleased", new int(SDL_KEYUP))
                .addVariable("TouchBegan", new int(SDL_FINGERDOWN))
                .addVariable("TouchEnded", new int(SDL_FINGERUP))
            .endNamespace()
            .beginNamespace("Keyboard")
                .addVariable("Left", new int(SDLK_LEFT))
                .addVariable("Right", new int(SDLK_RIGHT))
                .addVariable("Up", new int(SDLK_UP))
                .addVariable("Down", new int(SDLK_DOWN))
                .addVariable("A", new int(SDLK_a))
                .addVariable("B", new int(SDLK_b))
                .addVariable("C", new int(SDLK_c))
                .addVariable("D", new int(SDLK_d))
                .addVariable("E", new int(SDLK_e))
                .addVariable("F", new int(SDLK_f))
                .addVariable("G", new int(SDLK_g))
                .addVariable("H", new int(SDLK_h))
                .addVariable("I", new int(SDLK_i))
                .addVariable("J", new int(SDLK_j))
                .addVariable("K", new int(SDLK_k))
                .addVariable("L", new int(SDLK_l))
                .addVariable("M", new int(SDLK_m))
                .addVariable("N", new int(SDLK_n))
                .addVariable("O", new int(SDLK_o))
                .addVariable("P", new int(SDLK_p))
                .addVariable("Q", new int(SDLK_q))
                .addVariable("R", new int(SDLK_r))
                .addVariable("S", new int(SDLK_s))
                .addVariable("T", new int(SDLK_t))
                .addVariable("U", new int(SDLK_u))
                .addVariable("V", new int(SDLK_v))
                .addVariable("W", new int(SDLK_w))
                .addVariable("X", new int(SDLK_x))
                .addVariable("Y", new int(SDLK_y))
                .addVariable("Z", new int(SDLK_z))
            .endNamespace()
            .beginClass<LuaManager>("LuaManager")
                .addFunction("doFile", &LuaManager::doFile)
            .endClass()

            .beginClass<EntityState>("EntityState")
                .addData("entityId", &EntityState::entityId)
                .addData("position", &EntityState::position)
                .addData("angle", &EntityState::angle)
            .endClass()

            .beginClass<ActionManager>("ActionManager")
                .addFunction("getActionState", &ActionManager::getActionState)
                .addFunction("enableAction", &ActionManager::enableAction)
                .addFunction("disableAction", &ActionManager::disableAction)
                .addFunction("disableAll", &ActionManager::disableAll)
            .endClass()

            .beginClass<Layer>("Layer")
                .addFunction("createTile", &Layer::createTile)
                .addFunction("clearTiles", &Layer::clearTiles)
            .endClass()

            .beginClass<GameMap>("GameMap")
                .addFunction("getLayer", &GameMap::getLayer)
            .endClass()

            .beginClass<Scene>("Scene")
                .addFunction("getMap", &Scene::getMap)
            .endClass()

            .beginClass<SceneManager>("SceneManager")
                .addFunction("getCurrentScene", &SceneManager::getCurrentScene)
            .endClass()

            .beginClass<RenderTarget>("RenderTarget")
                .addFunction("getView", &Window::getView)
                .addFunction("setView", &Window::setView)
            .endClass()
            .deriveClass<Window, RenderTarget>("Window")
            .endClass()

            .beginClass<Vector2f>("Vector2f")
                .addConstructor<void (*) (float x, float y)>()
                .addData("x", &Vector2f::x)
                .addData("y", &Vector2f::y)
            .endClass()

            .beginClass<View>("View")
                .addFunction("setSize", &View::setSize)
                .addFunction("setCenter", &View::setCenter)
                .addFunction("getSize", &View::getSize)
            .endClass()
        .endNamespace();
}
