#include "ConfigExplorer.h"

bool ConfigExplorer::running = true;

ConfigExplorer::ConfigExplorer()
{
    //ctor
}

ConfigExplorer::~ConfigExplorer()
{
    //dtor
}

bool ConfigExplorer::renameSection(ConfigSection& c, Config& file)
{
    std::string key = Console::input(L("EnterKey"));
    std::string value = key + S("{}");

    size_t i = 0, j = 0;
    ConfigSection p;
    p.parse(&value, &i, &j);

    try
    {
        ConfigSection x = file.at(key);
    }
    catch(Exception e)
    {
        if(e == Error::ConfigAtSearchNotFound)
        {
            c.name = p.name;
            return true;
        } else
            throw(e);
    }
    return false;
}

bool ConfigExplorer::addSection(Config& c)
{
    std::string key = Console::input(L("EnterKey"));
    std::string value = key + S("{}");

    size_t i = 0, j = 0;
    ConfigSection p;
    p.parse(&value, &i, &j);

    try
    {
        ConfigSection x = c.at(key);
    }
    catch(Exception e)
    {
        if(e == Error::ConfigAtSearchNotFound)
        {
            c.sections.push_back(p);
            return true;
        } else
            throw(e);
    }
    return false;
}

bool ConfigExplorer::addKey(ConfigSection& c)
{
    std::string key = Console::input(L("EnterKey"));
    std::string valCmd = Console::input(L("EnterValue"));
    std::string value = key + S("=") + valCmd + S(";]");
    size_t i = 0, j = 0;
    Property p;
    p.parse(&value, &i, ']', &j);
    try
    {
        Property x = c.at(key);
    }
    catch(Exception e)
    {
        if(e == Error::ConfigAtSearchPropNotFound)
        {
            c.prop.push_back(p);
            return true;
        } else
            throw(e);
    }
    return false;
}

///@todo implement TableViewer
void ConfigExplorer::open(ConfigTable* ct, Config& file)
{
    std::cout << ConsoleBlocks::Error << L("NotYetImplemented") << "\n";
    return;
}

bool ConfigExplorer::open(Property& p, Config& file)
{
    std::string cmdAdd("");
    if(p.type()==PropertyType::LIST)
        cmdAdd = L("CfgExplorerKeyListCmd");
    else if(p.type()==PropertyType::TABLE)
        cmdAdd = L("CfgExplorerKeyTableCmd");

    std::string valCmd = Console::input(L("EnterValue")+S(" (")+L("CfgExplorerKeyCmd") + cmdAdd +S(")"));
    if(valCmd == "d")
        return true;
    else if(valCmd == "r")
        return false;
    else if(valCmd == "l")
    {
        open(p.valueLIST(), file);
        return false;
    }
    else if(valCmd == "t")
    {
        open(p.valueTABLE(), file);
        return false;
    }
    else if(valCmd == "rn")
    {
        p.name(Console::input(L("EnterKey")));
        return false;
    }
    std::string value = p.name() + S("=") + valCmd + S(";]");
    size_t i = 0, j = 0;
    p.parse(&value, &i, ']', &j);
    std::cout << "\n\n\n";
    return false;
}

void ConfigExplorer::open(ConfigSection& c, Config& file)
{
    while(running)
    {
        std::cout << ConsoleBlocks::Info << L("SelectCfgKey") << "\n";
        std::string THname = L("CfgExplorerTHName");
        std::string THtype = L("CfgExplorerTHType");
        std::string THvalue = L("CfgExplorerTHValue");

        size_t indexLen = (S("[n") + std::to_string(c.prop.size()-1) + S("] ")).size();
        std::cout   << Console::Header(StringHelper::blank(indexLen) +          THname
                                     + StringHelper::blank(25-THname.size()) +  THtype
                                     + StringHelper::blank(15-THtype.size()) +  THvalue, 100)
                    << "\n";
        for(size_t i = 0; i < c.prop.size(); i++)
        {
            std::string ident = S("[n") + std::to_string(i) + S("] ");
            std::cout   << ConsoleFormats::Bold << ident << StringHelper::blank(indexLen - ident.size()) << ConsoleFormats::Reset
                        << ConsoleFormats::LightCyan << c.prop[i].name() << ConsoleFormats::Reset
                        << StringHelper::blank(25-c.prop[i].name().size()) << ConsoleFormats::Dim       << Property::getStatusString(c.prop[i].type())
                        << StringHelper::blank(15-Property::getStatusString(c.prop[i].type()).size())   << StringHelper::limit(50, c.prop[i].getString()) << "\n";
        }

        std::cout << Console::Header(L("CfgExplorerKeyHint"), 100) << "\n";
        std::string command = Console::input(L("CfgExplorerEnterCmd"));
        try
        {
            if(command.substr(0, 1) == "n")
            {
                size_t intSection = StringHelper::to_int_strict(command.substr(1));
                if(intSection >= c.prop.size())
                    throw(Error::CfgExplorerPropDoesntExist);
                std::string ident = S("[n") + std::to_string(intSection) + S("] ");
                std::cout   << "\n" << L("SelectedEntry") << "\n" << ConsoleFormats::Inverted
                            << ConsoleFormats::Bold << ident << StringHelper::blank(indexLen - ident.size()) << ConsoleFormats::ResetBold
                            << ConsoleFormats::LightCyan << c.prop[intSection].name() << ConsoleFormats::Reset << ConsoleFormats::Inverted
                            << StringHelper::blank(25-c.prop[intSection].name().size()) << ConsoleFormats::Dim       << Property::getStatusString(c.prop[intSection].type())
                            << StringHelper::blank(15-Property::getStatusString(c.prop[intSection].type()).size())   << c.prop[intSection].getString() << ConsoleFormats::Reset << "\n\n";

                if(open(c.prop[intSection], file))
                    c.prop.erase(c.prop.begin() + intSection);
                file.save();
            } else if(command == "q")
            {
                running = false;
                return;
            } else if(command == "a")
            {
                if(addKey(c))
                    file.save();
            } else if(command == "rn")
            {
                if(renameSection(c, file))
                    file.save();
            } else if(command == "r")
            {
                std::cout << "\n\n\n";
                return;
            } else
            {
                std::cout << "\n\n\n";
                throw(Error::CfgExplorerUnknownCommand);
            }
        }
        catch(Exception e)
        {
            std::cout << e(L("CfgExplorerUnknownCmd"));
            return;
        }
    }
}

void ConfigExplorer::open(Config& c)
{
    while(running)
    {
        std::cout << ConsoleBlocks::Info << L("SelectCfg") << "\n";
        std::string THname = L("CfgExplorerTHName");
        std::string THtype = L("CfgExplorerTHType");

        size_t indexLenF = c.subSections.size()==0?0:((S("[ss") + std::to_string(c.subSections.size()-1) + S("] ")).size());
        size_t indexLenP = c.sections.size()==0?0:((S("[s") + std::to_string(c.sections.size()-1) + S("] ")).size());
        size_t indexLen = std::max(indexLenF, indexLenP);
        std::cout   << Console::Header(StringHelper::blank(indexLen)         + THname
                                     + StringHelper::blank(25-THname.size()) + THtype, 100)
                    << "\n";
        for(size_t i = 0; i < c.subSections.size(); i++)
        {
            std::string ident = S("[ss") + std::to_string(i) + S("] ");
            std::cout   << ConsoleFormats::Bold << ident << StringHelper::blank(indexLen - ident.size()) << ConsoleFormats::Reset
                        << ConsoleFormats::LightGreen << c.subSections[i].id << StringHelper::blank(25-c.subSections[i].id.size()) << ConsoleFormats::Reset
                        << ConsoleFormats::Dim << L("CfgExplorerSubsection") << ConsoleFormats::Reset << "\n";
        }

        for(size_t i = 0; i < c.sections.size(); i++)
        {
            std::string ident = S("[s") + std::to_string(i) + S("] ");
            std::cout   << ConsoleFormats::Bold << ident << StringHelper::blank(indexLen - ident.size()) << ConsoleFormats::Reset
                        << ConsoleFormats::LightYellow << c.sections[i].name << StringHelper::blank(25-c.sections[i].name.size())  << ConsoleFormats::Reset
                        << ConsoleFormats::Dim << L("CfgExplorerSection") << ConsoleFormats::Reset << "\n";
        }

        std::cout << Console::Header(L("CfgExplorerHint"), 100) << "\n";
        std::string command = Console::input(L("CfgExplorerEnterCmd"));
        std::cout << "\n\n\n";
        try
        {
            if(command.substr(0, 2) == "ss")
            {
                unsigned int intSection = StringHelper::to_int_strict(command.substr(2));
                if(intSection >= c.subSections.size())
                    throw(Error::CfgExplorerSSectionDoesntExist);
                open(c.subSections[intSection]);
            } else if(command.substr(0, 1) == "s")
            {
                unsigned int intSection = StringHelper::to_int_strict(command.substr(1));
                if(intSection >= c.sections.size())
                    throw(Error::CfgExplorerSectionDoesntExist);
                open(c.sections[intSection], c);
            } else if(command == "q")
            {
                running = false;
                return;
            } else if(command == "ac")
            {
                if(addSection(c))
                    c.save();
            } else if(command == "r")
            {
                return;
            } else
            {
                throw(Error::CfgExplorerUnknownCommand);
            }
        }
        catch(Exception e)
        {
            std::cout << e(L("CfgExplorerUnknownCmd"));
            return;
        }
    }
}

void ConfigExplorer::start()
{
    std::cout << Console::Header(L("CfgExplorer")) << "\n";
    open(Config::root);
}
