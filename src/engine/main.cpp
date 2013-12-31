#include "engine.h"
#include "commandlinearguments.h"

int main(int argc, char* argv[])
{
    Purity::CommandLineArguments arguments(argc, argv);
    
    Purity::Engine engine;

    engine.initialize(arguments);

    engine.run();

    engine.cleanup();

    return 0;
}
