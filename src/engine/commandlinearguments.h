#ifndef COMMAND_LINE_ARGUMENTS
#define COMMAND_LINE_ARGUMENTS

namespace Purity
{
    struct CommandLineArguments
    {
        CommandLineArguments();
        CommandLineArguments(int argc, char* argv[]);
    
        bool headless;
    };
}

#endif // COMMAND_LINE_ARGUMENTS
