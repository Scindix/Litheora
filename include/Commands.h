#ifndef COMMANDS_H
#define COMMANDS_H

#include <regex>
#include <thread>
#include <include.h>
#include "Language.h"
#include <App.h>
#include <ConfigExplorer.h>

#define NUM_MAX_CMD 10
#define NUM_MAX_PARAM 5

#define PARAM_DEFAULT  0x0
#define PARAM_OPTIONAL 0x1
#define PARAM_ARGUMENT 0x2
#define PARAM_READ     0x4

struct Parameter
{
    std::string name;
    char type;
    std::string shortName;
    std::string value;
    std::string description;
};

struct Command
{
    std::string name;
    void(*call)(Command);
    std::string description;
    Parameter parameter[NUM_MAX_PARAM];
};

class Commands
{
    public:
        Commands();
        virtual ~Commands();
        static void Help(Command);
        static void CommandLine(Command);
        static void NotImplemented(Command);
        static void SetProperty(Command);
        static void List(Command);
        static void Run(Command);

        static void init();
        static void call(std::vector<std::string>);
        static std::vector<Command> commands;
        static bool commandLineMode;
        static std::vector<std::thread> runningApps;
    protected:
    private:
};


#endif // COMMANDS_H
