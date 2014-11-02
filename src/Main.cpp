#include "Main.h"
Main::Main(std::vector<std::string> arguments)
{
    std::cout << APP.name << " (version: " << APP.version << ")\n";
#ifdef DEBUG_ARGS
    std::cout << "Command: " << APP.path << "\n";
    std::cout << "Execution path: " << APP.executionPath << "\n";
    std::cout << "Number of arguments: " << arguments.size() << "\n";
    for(unsigned int i = 0; i < arguments.size(); i++)
    {
        std::cout << "argument " << i << ": " << arguments[i] << "\n";
    }
#endif
    //CodeFile cf(S("./test.ph10"));
    //std::cout << ConsoleBlocks::Debug << LP("ShowingResultsFor", {"help"}) << "\n";
    __return = 0;
    App::init();
    try
    {
        Commands::call(arguments);
    }
    catch(Exception e)
    {
        std::cout << e(S(""));
        return;
    }
    catch(std::exception& e)
    {
        std::cout << Exception::errorString(e, "Main::Main(std::vector<std::string> arguments)");
        return;
    }
}

Main::~Main()
{
    //dtor
}
