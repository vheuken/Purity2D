#include "commandlinearguments.h"
#include <string>

Purity::CommandLineArguments::CommandLineArguments()
    : headless(false)
{
}

Purity::CommandLineArguments::CommandLineArguments(int argc, char* argv[])
    : CommandLineArguments()
{
    for (int i = 0; i < argc; ++i)
    {
        std::string arg(argv[i]);

        if (arg == "--headless")
        {
            headless = true;
        }
    }
}
