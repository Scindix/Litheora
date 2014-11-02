#include "Config.h"

Config Config::root;
Config Config::apps;
Config Config::app;
//std::vector<Config> Config::files;

Config::Config()
{
    //ctor
}

Config::~Config()
{
    //dtor
}

Config::Config(std::string s)
{
    if(parse(s))
        throw(Error::ConfigCriticalError);
}

Config::Config(std::string s, std::string bp)
{
    if(parse(s, bp))
        throw(Error::ConfigCriticalError);
}

void Config::save()
{
    std::string out("");
    out += S("@name ") + this->id + ";\n";
    for(size_t j = 0; j < sections.size(); j++)
    {
        out += sections[j].name + S("[");
        for(size_t k = 0; k < sections[j].param.size(); k++)
            out += sections[j].param[k].getSaveString();
        out += "]\n{";
        for(size_t k = 0; k < sections[j].prop.size(); k++)
        {
            out += "\n\t";
            out += sections[j].prop[k].getSaveString();
        }
        out += "\n}\n";
    }
    for(size_t j = 0; j < subSections.size(); j++)
    {
        out += S("@include \"") + subSections[j].fname.substr((APP.basePath + PATH_SLASH).size()) + "\";\n";
        subSections[j].save();
    }
    File::Text outFile(fname);
    outFile << out;
}

void Config::init(std::string base)
{
    std::string resultPath;
    try
    {
        File::Folder f(APP.executionPath);
        std::string out("");
        try
        {
            File::Text file;
            f.up();
            resultPath = f.path + PATH_SLASH + base;
            file = resultPath;
            file >> out;
            APP.basePath = f.path;
        } catch(Exception e)
        {
            if(e == Error::TextFileReadError)
            {
                try
                {
                    File::Text file;
                    f.up();
                    resultPath = f.path + PATH_SLASH + base;
                    file = resultPath;
                    file >> out;
                    APP.basePath = f.path;
                }
                catch(Exception e)
                {
                    if(e == Error::TextFileReadError)
                    {
                        std::cout << e(S("Config file is missing: '") + resultPath + S("' or '") + f.up().path + PATH_SLASH + base + S("'"));
                        std::cout << ConsoleBlocks::Error << "You cannot start " << APP.name << " without a working config database!\n";
                        exit(-1);
                    }
                    throw(e);
                }
            } else
                throw(e);
        }
        if(root.parse(out))
        {
            throw(Error::ConfigCriticalError);
        }
        root.fname = resultPath;
        root.id = base.substr(0, base.find(".", base.rfind(PATH_SLASH)+1));

        for(Property p : (root%"Apps").prop)
        {
            std::string indexFile = APP.basePath + PATH_SLASH + (p.valueLIST()/"index").valueSTRING();
            File::Text file(indexFile.c_str());
            file >> indexFile;
            Config appC;
            appC.parse(indexFile);
            p.valueLIST().prop.push_back(Property(S("App"), *new ConfigSection(appC%"App")));
            p.valueLIST().name = "App";
            p.valueLIST().param = (appC%"App").param;
            apps.sections.push_back(p.valueLIST());
        }
    }
    catch(Exception e)
    {
        std::cout << e(S("Problem in config file: '") + Console::FileAdress(base) + S("'"));
        std::cout << ConsoleBlocks::Error << "You cannot start " << APP.name << " without a working config database!\n";
        exit(-1);
    }
    catch(std::exception& e)
    {
        std::cout << Exception::errorString(e, "void Config::init(std::string base)");
        return;
    }
}

void Config::initApp(size_t index)
{
    std::string startStr = ((apps.sections[index]/"App").valueLIST()/"index").valueSTRING();
    File::Text fs = S((apps.sections[index]/"index").valueSTRING());
    File::Text f(startStr, fs.parent());
    std::string fileCont;
    f >> fileCont;

    Config::app.parse(fileCont, fs.parent().getPath());
}

Config& Config::atSub(std::string needle)
{
    for(size_t i = 0; i < subSections.size(); i++)
    {
        if(subSections[i].id == needle)
        {
            return subSections[i];
        }
    }
    throw(Error::ConfigAtSearchNotFound);
}

Config& Config::operator/ (std::string s)
{
    return atSub(s);
}

ConfigSection& Config::operator% (std::string s)
{
    return at(s);
}

ConfigSection& Config::at(std::string needle)
{
    return at(needle, *new std::vector<std::string>);
}

ConfigSection& Config::at(std::string needle, std::vector<std::string> pattern)
{
    int* i = new int;
    ConfigSection& cs = at(needle, pattern, i);
    delete i;
    return cs;
}

ConfigSection& Config::at(std::string needle, std::vector<std::string> pattern, int* index)
{
    if(pattern.size()%2 == 1)
        throw(Error::ConfigAtSearchMod2);
    for(size_t i = 0; i < sections.size(); i++)
    {
        if(sections[i].name == needle)
        {
            if(pattern.size()==0)
            {
                *index = i;
                return sections[i];
            }
            for(size_t j = 0; j < pattern.size(); j+=2)
            {
                for(size_t k = 0; k < sections[i].param.size(); k++)
                {
                    if(sections[i].param[k].name() == pattern[j] && sections[i].param[k].valueSTRING() == pattern[j+1])
                    {
                        *index = i;
                        return sections[i];
                    }
                }
            }
        }
    }
    throw(Error::ConfigAtSearchNotFound);
}

bool Config::parse(std::string s)
{
    parse(s, APP.basePath);
}

bool Config::parse(std::string s, std::string basePath)
{
    size_t i = 0;
    size_t lineNumber = 1;
    while(true)
    {
    std::cout << "starting:" << s.substr(i, 20) << "\n";
        ConfigSection c;
        try
        {
            while(s.substr(i,1) == " " || s.substr(i,1) == "\t" || s.substr(i,1) == "\n")
            {
                if(s.substr(i,1) == "\n")
                    lineNumber++;
                i++;
                if(i+1 == s.size())
                    break;
            }
            if(s.substr(i,1) == "@")
            {
                if(s.substr(i,8) == "@include")
                {
                    std::string argument("");
                    size_t pos;
                    i+=8;
                    while(s.substr(i,1) == " " || s.substr(i,1) == "\t" || s.substr(i,1) == "\n")
                    {
                        if(s.substr(i,1) == "\n")
                            lineNumber++;
                        i++;
                        if(i+1 == s.size())
                            throw(Error::ConfigPreprocessorUnclosed);
                    }
                    if(s.substr(i,1) == "\"")
                    {
                        pos = s.find("\"", i+1);
                        if(pos == std::string::npos)
                            throw(Error::ConfigWrongPreprocessorStringArgSyntax);
                        argument = s.substr(i+1, pos-i-1);
                    } else
                    {
                        throw(Error::ConfigWrongPreprocessorStringArgSyntax);
                    }
                    File::Text file(argument, basePath);
                    std::string out("");
                    file >> out;
                    Config _c;
                    std::string sf = argument;
                    StringHelper::replaceAll(sf, "./", "");
                    _c.id = sf.substr(0, sf.find(".", sf.rfind(PATH_SLASH)+1));
                    _c.fname = S(file.filename);
                    if(_c.parse(out, basePath))
                        throw(Error::ConfigCriticalError);

                    subSections.push_back(_c);
                    while(s.substr(i,1) == " " || s.substr(i,1) == "\t" || s.substr(i,1) == "\n")
                    {
                        if(s.substr(i,1) == "\n")
                            lineNumber++;
                        i++;
                        if(i+1 == s.size())
                            throw(Error::ConfigPreprocessorUnclosed);
                    }
                    i = pos+1;
                    if(s.substr(i,1) != ";")
                        throw(Error::ConfigPreprocessorUnclosed);
                    else
                        i++;
                } else if(s.substr(i,5) == "@name")
                {
                    i+=5;
                    try
                    {
                        ParserHelper::skipSpaces(&i, &s, &lineNumber);
                        id = ParserHelper::getWord(&i, &s, &lineNumber, KeyWD::SemiColon);
                        ParserHelper::skipSpaces(&i, &s, &lineNumber);
                    } catch(Exception e)
                    {
                        throw(Error::ConfigNotAValidFileId);
                    }
                    if(s.substr(i,1) != ";")
                        throw(Error::ConfigPreprocessorUnclosed);
                    else
                        i++;
                } else if(s.substr(i,6) == "@index")
                {
                    std::cout << "index found\n";
                    i+=7;
                    try
                    {
                    std::cout << "index parse1\n";

                        if(s.substr(i,1) == "%")
                            i++;
                        else
                            throw(Error::ConfigOnlyVirtAppPathSupport);
                        id = ParserHelper::getWord(&i, &s, &lineNumber, "%");
                    std::cout << "index parse2\n";
                        if(id == "VIRTUAL_APP_PATH" && s.substr(i,1) == "%")
                            i++;
                        else
                            throw(Error::ConfigOnlyVirtAppPathSupport);
                        CodePackage cp(&i, &s, &lineNumber, S("%VIRTUAL_APP_PATH%"));
                        Property p("root", cp);
                        ConfigSection cs;
                        cs.prop.push_back(p);
                        this->sections.push_back(cs);
                        ParserHelper::skipSpaces(&i, &s, &lineNumber);
                    } catch_auto //

                    std::cout << "index parse3: " << i << ": \n\n\n" << s << "\n";
                    if(s.substr(i,1) != ";")
                        throw(Error::ConfigPreprocessorUnclosed);
                    else
                        i++;

                    std::cout << "index parse4\n";
                } else
                {
                    throw(Error::ConfigUnknownPreprecessorDirective);
                }
            }
            else
            {
    std::cout << "parse :" << s.substr(i, 20) << "\n";
                if(c.parse(&s, &i, &lineNumber))
                {
                    sections.push_back(c);
                }
                else
                    break;
            }

        }
        catch(Exception e)
        {
            std::vector<std::string> lines = StringHelper::explode(s, '\n');
            size_t columnNumber = 0;
            for(size_t i = 0; i < lineNumber-1; i++)
            {
                columnNumber += lines[i].size()+1;
            }
            int posInCol = int(i)-int(columnNumber);
            std::cout << e(__S__("While parsing:\n\t '") + s.substr(0, 15) + __S__("[...]'\n\n\tIn Line ") + std::to_string(lineNumber)
                           + __S__(", Column ") + std::to_string(posInCol) + __S__(": ")
                           + ConsoleFormats::RedBack + ConsoleFormats::Bold + lines[lineNumber-1].substr(std::max((int)0, posInCol-20), 20 + std::min((int)0, posInCol-20))
                           + ConsoleFormats::YellowBack + lines[lineNumber-1].at(posInCol)
                           + ConsoleFormats::RedBack + lines[lineNumber-1].substr(posInCol+1) + StringHelper::blank(5) + ConsoleFormats::Reset);
            return true;
        }
        catch(std::exception& e)
        {
            std::cout << Exception::errorString(e, "Config::parse(std::string s)");
            return true;
        }
    }
    return false;
}

Config& Config::operator= (std::string s)
{
    parse(s);
    return *this;
}
