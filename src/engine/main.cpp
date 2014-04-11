#include "engine.h"
#include "commandlinearguments.h"

// HACK!
// SDL2 redefines main, which messes with Windows
#ifdef _WIN32
#undef main
#endif

int main(int argc, char* argv[])
{
    const Purity::CommandLineArguments arguments(argc, argv);

    Purity::Engine engine(arguments);

    engine.run();

    return 0;
}
