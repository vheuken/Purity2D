#include "luamanager.h"

#include <SFML/Graphics.hpp>
#include <lua.hpp>
#include <luabind/luabind.hpp>
#include "../framework/entity.h"
#include "../framework/movableentity.h"
#include "../framework/objectmanager.h"
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
    luaL_dofile(mLuaState, luaFileName.c_str());
}

void Purity::LuaManager::loadFile(const std::string& luaFileName)
{
    luaL_loadfile(mLuaState, luaFileName.c_str());
}

void Purity::LuaManager::initializeBindings()
{
    luabind::open(mLuaState);

    initializeSFMLBindings();

    luabind::module(mLuaState) [
        ObjectManager::luaBindings(),
        Entity::luaBindings(),
        MovableEntity::luaBindings(),
        Engine::luaBindings()
    ];
    
}

void Purity::LuaManager::initializeSFMLBindings()
{    
    luabind::open(mLuaState);
    luabind::module(mLuaState)
    [
        luabind::class_<sf::Keyboard>("Keyboard")
            .enum_("Key")
            [
                luabind::value("A", sf::Keyboard::Key::A),
                luabind::value("B", sf::Keyboard::Key::B),
                luabind::value("C", sf::Keyboard::Key::C),
                luabind::value("D", sf::Keyboard::Key::D),
                luabind::value("E", sf::Keyboard::Key::E),
                luabind::value("F", sf::Keyboard::Key::F),
                luabind::value("G", sf::Keyboard::Key::G),
                luabind::value("H", sf::Keyboard::Key::H),
                luabind::value("I", sf::Keyboard::Key::I),
                luabind::value("J", sf::Keyboard::Key::J),
                luabind::value("K", sf::Keyboard::Key::K),
                luabind::value("L", sf::Keyboard::Key::L),
                luabind::value("M", sf::Keyboard::Key::M),
                luabind::value("N", sf::Keyboard::Key::N),
                luabind::value("O", sf::Keyboard::Key::O),
                luabind::value("P", sf::Keyboard::Key::P),
                luabind::value("Q", sf::Keyboard::Key::Q),
                luabind::value("R", sf::Keyboard::Key::R),
                luabind::value("S", sf::Keyboard::Key::S),
                luabind::value("T", sf::Keyboard::Key::T),
                luabind::value("U", sf::Keyboard::Key::U),
                luabind::value("V", sf::Keyboard::Key::V),
                luabind::value("W", sf::Keyboard::Key::W),
                luabind::value("X", sf::Keyboard::Key::Z),
                luabind::value("Y", sf::Keyboard::Key::Y),
                luabind::value("Z", sf::Keyboard::Key::Z),
                luabind::value("Num0", sf::Keyboard::Key::Num0),
                luabind::value("Num1", sf::Keyboard::Key::Num1),
                luabind::value("Num2", sf::Keyboard::Key::Num2),
                luabind::value("Num3", sf::Keyboard::Key::Num3),
                luabind::value("Num4", sf::Keyboard::Key::Num4),
                luabind::value("Num5", sf::Keyboard::Key::Num5),
                luabind::value("Num6", sf::Keyboard::Key::Num6),
                luabind::value("Num7", sf::Keyboard::Key::Num7),
                luabind::value("Num8", sf::Keyboard::Key::Num8),
                luabind::value("Num9", sf::Keyboard::Key::Num9),
                luabind::value("Escape", sf::Keyboard::Key::Escape),
                luabind::value("LControl", sf::Keyboard::Key::LControl),
                luabind::value("LShift", sf::Keyboard::Key::LShift),
                luabind::value("LAlt", sf::Keyboard::Key::LAlt),
                luabind::value("LSystem", sf::Keyboard::Key::LSystem),
                luabind::value("RControl", sf::Keyboard::Key::RControl),
                luabind::value("RShift", sf::Keyboard::Key::RShift),
                luabind::value("RAlt", sf::Keyboard::Key::RAlt),
                luabind::value("RSystem", sf::Keyboard::Key::RSystem),
                luabind::value("Menu", sf::Keyboard::Key::Menu),
                luabind::value("LBracket", sf::Keyboard::Key::LBracket),
                luabind::value("RBracket", sf::Keyboard::Key::RBracket),
                luabind::value("SemiColon", sf::Keyboard::Key::SemiColon),
                luabind::value("Comma", sf::Keyboard::Key::Comma),
                luabind::value("Period", sf::Keyboard::Key::Period),
                luabind::value("Quote", sf::Keyboard::Key::Quote),
                luabind::value("Slash", sf::Keyboard::Key::Slash),
                luabind::value("BackSlash", sf::Keyboard::Key::BackSlash),
                luabind::value("Tilde", sf::Keyboard::Key::Tilde),
                luabind::value("Equal", sf::Keyboard::Key::Equal),
                luabind::value("Dash", sf::Keyboard::Key::Dash),
                luabind::value("Space", sf::Keyboard::Key::Space),
                luabind::value("Return", sf::Keyboard::Key::Return),
                luabind::value("BackSpace", sf::Keyboard::Key::BackSpace),
                luabind::value("Tab", sf::Keyboard::Key::Tab),
                luabind::value("PageUp", sf::Keyboard::Key::PageUp),
                luabind::value("PageDown", sf::Keyboard::Key::PageDown),
                luabind::value("End", sf::Keyboard::Key::End),
                luabind::value("Home", sf::Keyboard::Key::Home),
                luabind::value("Insert", sf::Keyboard::Key::Insert),
                luabind::value("Delete", sf::Keyboard::Key::Delete),
                luabind::value("Add", sf::Keyboard::Key::Add),
                luabind::value("Subtract", sf::Keyboard::Key::Subtract),
                luabind::value("Multiply", sf::Keyboard::Key::Multiply),
                luabind::value("Divide", sf::Keyboard::Key::Divide),
                luabind::value("Left", sf::Keyboard::Key::Left),
                luabind::value("Right", sf::Keyboard::Key::Right),
                luabind::value("Up", sf::Keyboard::Key::Up),
                luabind::value("Down", sf::Keyboard::Key::Down),
                luabind::value("Numpad0", sf::Keyboard::Key::Numpad0),
                luabind::value("Numpad1", sf::Keyboard::Key::Numpad1),
                luabind::value("Numpad2", sf::Keyboard::Key::Numpad2),
                luabind::value("Numpad3", sf::Keyboard::Key::Numpad3),
                luabind::value("Numpad4", sf::Keyboard::Key::Numpad4),
                luabind::value("Numpad5", sf::Keyboard::Key::Numpad5),
                luabind::value("Numpad6", sf::Keyboard::Key::Numpad6),
                luabind::value("Numpad7", sf::Keyboard::Key::Numpad7),
                luabind::value("Numpad8", sf::Keyboard::Key::Numpad8),
                luabind::value("Numpad9", sf::Keyboard::Key::Numpad9),
                luabind::value("F1", sf::Keyboard::Key::F1),
                luabind::value("F2", sf::Keyboard::Key::F2),
                luabind::value("F3", sf::Keyboard::Key::F3),
                luabind::value("F4", sf::Keyboard::Key::F4),
                luabind::value("F5", sf::Keyboard::Key::F5),
                luabind::value("F6", sf::Keyboard::Key::F6),
                luabind::value("F7", sf::Keyboard::Key::F7),
                luabind::value("F8", sf::Keyboard::Key::F8),
                luabind::value("F9", sf::Keyboard::Key::F9),
                luabind::value("F10", sf::Keyboard::Key::F10),
                luabind::value("F11", sf::Keyboard::Key::F11),
                luabind::value("F12", sf::Keyboard::Key::F12),
                luabind::value("F13", sf::Keyboard::Key::F13),
                luabind::value("F14", sf::Keyboard::Key::F14),
                luabind::value("F15", sf::Keyboard::Key::F15),
                luabind::value("Pause", sf::Keyboard::Key::Pause),
                luabind::value("KeyCount", sf::Keyboard::Key::KeyCount)
            ],

        luabind::class_<sf::Event>("Event")
            .def(luabind::constructor<>())
            .def_readonly("Type", &sf::Event::type)
            .enum_("EventType")
            [
                luabind::value("Closed", 0),
                luabind::value("Resized", 1),
                luabind::value("LostFocus", 2),
                luabind::value("GainedFocus", 3),
                luabind::value("TextEntered", 4),
                luabind::value("KeyPressed", 5),
                luabind::value("KeyReleased", 6),
                luabind::value("MouseWheelMoved", 7),
                luabind::value("MousePressed", 8),
                luabind::value("MouseReleased", 9),
                luabind::value("MouseMoved", 10),
                luabind::value("MouseEntered", 11),
                luabind::value("MouseLeft", 12)
            ]
            .def_readonly("Key", &sf::Event::key)
            .def_readonly("Mouse", &sf::Event::mouseMove),

            luabind::class_<sf::Event::KeyEvent>("KeyEvent")
                .def_readonly("Code", &sf::Event::KeyEvent::code)
                .def_readonly("Alt", &sf::Event::KeyEvent::alt)
                .def_readonly("Control", &sf::Event::KeyEvent::control)
                .def_readonly("Shift", &sf::Event::KeyEvent::shift),

            luabind::class_<sf::View>("View")
                .def(luabind::constructor<>())
                .def("Reset", &sf::View::reset)
                .def("Zoom", &sf::View::zoom)
                .def("Rotate", &sf::View::rotate)
                .def("Move", (void (sf::View::*)(float, float))&sf::View::move)
                .def("GetCenter", &sf::View::getCenter)
                .def("GetSize", &sf::View::getSize)
                .def("SetCenter", (void (sf::View::*)(float, float))&sf::View::setCenter),

            luabind::class_<sf::Vector2f>("Vector2f")
                .def(luabind::constructor<float, float>())
                .def_readwrite("x", &sf::Vector2f::x)
                .def_readwrite("y", &sf::Vector2f::y)

    ];
}