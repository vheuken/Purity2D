#include "engine.h"
#include "commandlinearguments.h"

int main(int argc, char* argv[])
{
    const Purity::CommandLineArguments arguments(argc, argv);
    
    Purity::Engine engine(arguments);

    engine.initialize();

    engine.run();

    engine.cleanup();

    return 0;
}
