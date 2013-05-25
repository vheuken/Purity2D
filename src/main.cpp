#include <iostream>
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <lua.hpp>
#include <luabind/luabind.hpp>

void sayhi()
{
	std::cout << "YO YO YO" << std::endl;
}

int main()
{
	
	lua_State* L;

	std::cout << "Testing SFML Window..." << std::endl;
	
	// SFML link testing..
	
	sf::Window window(sf::VideoMode(800, 600), "My window");

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
	
	/* initialize Lua */
	L = luaL_newstate();

	luabind::module(L)
	[
		luabind::def("sayHI", &sayhi)
	];

	/* load Lua base libraries */
	luaL_openlibs(L);

	/* run the script */
	luaL_dofile(L, "test.lua");

	/* cleanup Lua */
	lua_close(L);

	/* pause */
	printf( "Press enter to exit..." );
	getchar();

	return 0;
}