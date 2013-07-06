#include "engine.h"

int main()
{
	Purity::Engine engine;

    engine.initialize();

    engine.run();

    engine.cleanup();

	return 0;
}