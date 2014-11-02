#include "Commands.h"

std::vector<Command> Commands::commands;
bool Commands::commandLineMode = false;
std::vector<std::thread> Commands::runningApps;

Commands::Commands()
{
    //ctor
}

Commands::~Commands()
{
    //dtor
}

void Commands::CommandLine(Command c)
{
    commandLineMode = true;
    while(1)
    {
        std::string inputCmd = Console::input("~> ");
        std::string chkCmd = inputCmd;
        StringHelper::replaceAll(chkCmd, " ", "");
        StringHelper::replaceAll(chkCmd, "\t", "");
        if(chkCmd == "")
            continue;
        if(inputCmd == "exit")
        {
            for(size_t i = 0; i < runningApps.size(); i++)
                runningApps[i].join();
            commandLineMode = false;
            break;
        }
        size_t cutOffset = 0;
        size_t oldOffset = 0;
        std::vector<std::string> commands;
        while(1)
        {
            size_t offset = inputCmd.find(" ", oldOffset);
            if(offset == std::string::npos)
            {
                commands.push_back(inputCmd.substr(cutOffset));
                break;
            }
            else
            {
                size_t offsetQuotes = inputCmd.find("\"", oldOffset);
                if(offsetQuotes > offset)
                {
                    commands.push_back(inputCmd.substr(cutOffset, offset-cutOffset));
                    oldOffset = offset+1;
                    cutOffset = oldOffset;
                } else
                {
                    offsetQuotes = inputCmd.find("\"", offsetQuotes+1);
                    oldOffset = offsetQuotes+1;
                }
            }
        }
        call(commands);
        commandLineMode = true;
    }
}

void Commands::SetProperty(Command c)
{
    std::string setLang;
    if(c.parameter[0].value == "s")
    {
        std::cout << ConsoleBlocks::Info << L("SelectLanguage") << "\n";
        for(size_t i = 0; i < Language::languages->sections.size(); i++)
        {
            std::cout << "[" << i << "] " << Language::languages->sections[i].atParam(S("Title")).valueSTRING() << " (" << Language::languages->sections[i].atParam(S("Code")).valueSTRING() << ")\n";
        }
        std::string newLang = Console::input(L("ChooseLanguage"));
        unsigned int intLang;
        try
        {
            intLang = StringHelper::to_int_strict(newLang);
        }
        catch(Exception e)
        {
            std::cout << e(S("You didn't provide an integer value (strict)"));
            return;
        }
        if(intLang < Language::languages->sections.size())
            setLang = S("language{Language=\"") + Language::languages->sections[intLang].atParam(S("Code")).valueSTRING() + S("\";}");
        else
            throw(Error::SetLanguageNotAvailable);
    }
    else if(c.parameter[0].value != S("/"))
        setLang = S("language{Language=\"") + c.parameter[0].value + S("\";}");

    std::string changes = c.parameter[1].value + setLang;
    if(c.parameter[2].value != S(" "))
    {
        if(c.parameter[2].value == "*")
            ConfigExplorer::open(Config::apps);
        else if(c.parameter[2].value == "~")
            ConfigExplorer::open(Config::app);
        else
            std::cout << ConsoleBlocks::Warning << L("NotYetImplemented");
        //ConfigExplorer::open();
    }
    else if(changes == " ")
    {
        ConfigExplorer::start();
    }
    if(changes == " ")
        return;

    Config con(changes);
    try
    {
        for(size_t i = 0; i < con.sections.size(); i++)
        {
            std::vector<std::string> pattern;
            std::string sectionName = con.sections[i].name;
            for(size_t j = 0; j < con.sections[i].param.size(); j++)
            {
                pattern.push_back(con.sections[i].param[j].name());
                pattern.push_back(con.sections[i].param[j].valueSTRING());
            }
            for(size_t j = 0; j < con.sections[i].prop.size(); j++)
            {
                if(Config::root.at(sectionName, pattern).at(con.sections[i].prop[j].name()).type() == con.sections[i].prop[j].type())
                {
                    Config::root.at(sectionName, pattern).at(con.sections[i].prop[j].name()) = con.sections[i].prop[j];
                }
                else
                    throw(Error::ConfigWrongType);
            }
        }
        Config::root.save();
    }
    catch(Exception e)
    {
        std::cout << e(S("While parsing '") + changes + S("'"));
        return;
    }
    catch(std::exception& e)
    {
        std::cout << Exception::errorString(e, "void Commands::SetProperty(Command c)");
        return;
    }
}

void Commands::Help(Command c)
{
    std::cout << Console::Header(L("HelpReference")) << "\n";
    std::string regex = ExpHelper::genRegEx(c.parameter[0].value);
    std::regex reg = std::regex(regex);
    std::cout << LP("ShowingResultsFor", {regex}) << "\n\n";
    for(size_t i = 0; i < commands.size(); i++)
    {
        if(commands[i].name == S(""))
            break;
        if(!std::regex_match(commands[i].name, reg))
            continue;
        std::cout << "  " << ConsoleFormats::Bold << commands[i].name << ConsoleFormats::Reset;
        for(int j = 0; j < NUM_MAX_PARAM; j++)
        {
            if(commands[i].parameter[j].name == S(""))
                break;
            bool b = commands[i].parameter[j].type & PARAM_OPTIONAL;
            std::cout << "  " << ConsoleFormats::LightBlueBack << (b?"[":"") << "--" << commands[i].parameter[j].name << (b?"]":"") << ConsoleFormats::Reset;
        }
        std::cout << "\n   " << commands[i].description << "\n";
        for(int j = 0; j < NUM_MAX_PARAM; j++)
        {
            if(commands[i].parameter[j].name == S(""))
                break;
            std::cout << "   " << ConsoleFormats::Underlined << "--" << commands[i].parameter[j].name << ConsoleFormats::Reset << " " << LP("CommandAlternative", {commands[i].parameter[j].shortName}) << "\n";
            std::cout << "    " << commands[i].parameter[j].description << "\n\n";
        }
        std::cout << "\n\n";
    }
}

void Commands::Run(Command c)
{
    std::string appStr = c.parameter[0].value;
    if(appStr == "~")
        appStr = (Config::root%"arelium"/"lastApp").valueSTRING();

    int* index = new int;
    ConfigSection& appCS = Config::apps.at("App", {"id", appStr}, index);
    Config::initApp(*index);

    App* a = new App();

    if(c.parameter[1].value == "false")
    {
        a->start();
        Config::app = Config();
    } else
    {
        runningApps.push_back
        (
            std::thread
            (
                [a](){a->start();}
            )
        );
        if(!commandLineMode)
            call({"command"});
    }
}

void Commands::List(Command c)
{
    std::regex reg = std::regex(ExpHelper::genRegEx(c.parameter[0].value));

    for(ConfigSection app : Config::apps.sections)
    {
        ConfigSection cs = (app/"App").valueLIST();
        std::string cmpStr = (cs/"name").valueSTRING();

        if(std::regex_match(cmpStr, reg))
        {
            std::string title = (cs/"title").valueSTRING();
            if(c.parameter[1].value == "true")
                title = cs.atParam("id").valueSTRING();
            std::cout   << ConsoleFormats::Bold << title << " \t"
                        << ConsoleFormats::Dim << (cs/"description").valueSTRING()
            << ConsoleFormats::Reset << "\n";
        }
    }
}

void Commands::NotImplemented(Command c)
{
    std::cout << ConsoleBlocks::Error << "Well, this is embarassing, but this command doesn't seem to be implemented, but it is defined! Be sure to file a bug.\n";
}

void Commands::init()
{
    commands =
    {
        {
            "--help",
            &Commands::Help,
            L("CommandHelpDescription"),
            {
                {
                    "command",
                    PARAM_OPTIONAL,
                    "c",
                    "<string>=(.*)",
                    L("CommandHelpParamCommandFilterDescription")
                }
            }
        },
        {
            "set",
            &Commands::SetProperty,
            L("CommandSetDescription"),
            {
                {
                    "language",
                    PARAM_OPTIONAL,
                    "l",
                    "<string>=/",
                    L("CommandSetParamLangDescription")
                },
                {
                    "property",
                    PARAM_OPTIONAL,
                    "p",
                    "<string>= ",
                    L("CommandSetParamPropDescription")
                },
                {
                    "apps",
                    PARAM_OPTIONAL,
                    "a",
                    "<string>= ",
                    L("CommandSetParamAppsDescription")
                }
            }
        },
        {
            "command",
            &Commands::CommandLine,
            L("CommandCommandLine"),
            {}
        },
        {
            "list",
            &Commands::List,
            L("CommandList"),
            {
                {
                    "filter",
                    PARAM_OPTIONAL,
                    "f",
                    "<string>=(.*)",
                    L("CommandHelpParamListFilterDescription")
                },
                {
                    "verbose",
                    PARAM_OPTIONAL,
                    "v",
                    "<bool>=false",
                    L("CommandHelpParamListVerboseDescription")
                }
            }
        },
        {
            "run",
            &Commands::Run,
            L("CommandRun"),
            {
                {
                    "app",
                    PARAM_DEFAULT,
                    "a",
                    "<string>=~",
                    L("CommandHelpParamRunAppDescription")
                },
                {
                    "new-thread",
                    PARAM_OPTIONAL,
                    "t",
                    "<bool>=false",
                    L("CommandHelpParamRunNewTDescription")
                }
            }
        }
    };
}

void Commands::call(std::vector<std::string> _s)
{
    std::vector<std::string> s = _s;
    int cmd = -1;
    Command p;
    if(s.size() == 0)
    {
        s = {APP.standardCmd};
        std::cout << ConsoleBlocks::Info << "You didn't provide any commands. Using standard command `" << APP.standardCmd << "` (This is by design)\n";
    }
    for(size_t i = 0; i < commands.size(); i++)
    {
        if(commands[i].name == S(""))
            break;
        else if(commands[i].name == s[0])
        {
            cmd = i;
            break;
        }
    }
    if(cmd == -1)
    {
        std::cout << ConsoleBlocks::Error << "This command doesn't exist. Please type `" << APP.command << " --help` for help\n";
        return;
    }
    p = commands[cmd];
    for(unsigned int i = 1; i < s.size(); i++)
    {
        bool argumentIsUsed = false;
        for(int j = 0; j < NUM_MAX_PARAM; j++)
        {
            if(p.parameter[j].name == S(""))
                break;
            if((S("--") + p.parameter[j].name) == s[i] || (S("-") + p.parameter[j].shortName) == s[i])
            {
                argumentIsUsed = true;
                if(p.parameter[j].type & PARAM_READ)
                {
                    std::cout << ConsoleBlocks::Warning << "The Parameter `" << p.parameter[j].name << "` is used twice or more. Only the first occurence is considered.\n";
                } else
                {
                    p.parameter[j].type |= PARAM_READ;
                    std::vector<std::string> val = StringHelper::explode(p.parameter[j].value, '=');
                    if(val[0] == S("<bool>"))
                        p.parameter[j].value = S("true");
                    else
                    {
                        if(s.size() < ++i+1)
                        {
                            std::cout << ConsoleBlocks::Error << "The Parameter `" << p.parameter[j].name << "` doesn't provide any values. But it needs one. Please type `" << APP.command << " --help` for help\n";
                            exit(-1);
                        }
                        p.parameter[j].value = s[i];
                    }
                }
            }
        }
        if(!argumentIsUsed)
            std::cout << ConsoleBlocks::Warning << "The Parameter `" << s[i] << "` is unknown. It is ignored!\n";
    }
    for(int j = 0; j < NUM_MAX_PARAM; j++)
    {
        if(p.parameter[j].name == S(""))
            break;
        if((p.parameter[j].type & PARAM_READ) == 0)
        {
            if((p.parameter[j].type & PARAM_OPTIONAL) == 0)
            {
                std::cout << ConsoleBlocks::Error << "The Parameter `" << p.parameter[j].name << "` is not optional!\n";
                return;
            } else
            {
                std::vector<std::string> val = StringHelper::explode(p.parameter[j].value, '=');
                p.parameter[j].value = val[1];
            }
        }
    }
    p.call(p);
}
