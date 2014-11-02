#include "Text.h"

namespace File
{
    Text::Text() {}

    Text::Text(std::string p, std::string appBase)
    {
        if(appBase.substr(0, PATH_SLASH.size()) == PATH_SLASH)
            appBase = appBase.substr(1);
        if(appBase.substr(appBase.size()-PATH_SLASH.size(), PATH_SLASH.size()) != PATH_SLASH)
            appBase = appBase + PATH_SLASH;
        std::string path;
        if(p.substr(0, PATH_SLASH.size()+1) == "." + PATH_SLASH)
            path = APP.basePath + PATH_SLASH + appBase + p.substr(2);
        else if(p.substr(0, PATH_ROOT.size()) != PATH_ROOT)
            path = APP.basePath + PATH_SLASH + p;
        else
            path = p;
        load(path);
    }

    Text::Text(std::string p, Folder appBase)
    {
        std::string path;
        if(p.substr(0, PATH_SLASH.size()+1) == "." + PATH_SLASH)
            path = APP.basePath + appBase.getPath() + p.substr(2);
        else if(p.substr(0, PATH_ROOT.size()) != PATH_ROOT)
            path = APP.basePath + PATH_SLASH + p;
        else
            path = p;
        load(path);
    }

    Text::Text(std::string f)
    {
        load(f);
    }

    Text::Text(const char* f)
    {
        load(f);
    }

    void Text::operator=(std::string f)
    {
        load(f);
    }

    void Text::operator=(const char* f)
    {
        load(f);
    }

    void Text::load(std::string f)
    {
        load(f.c_str());
    }

    void Text::load(const char* f)
    {
        filename = (new S(f))->c_str();
    }

    Text& Text::operator<<(std::string& s)
    {
#ifdef DEBUG_WRITE_FILE
        std::cout << ConsoleBlocks::Debug << LP("WriteToFile", {Console::FileAdress(filename)}) << std::endl;
#endif
        std::ofstream out(filename, std::ios::out | std::ios::binary);
        if(out)
        {
            out << s;
            out.close();
        }
        else
        {
#ifdef DEBUG_WRITE_FILE
            std::cout << ConsoleBlocks::Debug << ConsoleBlocks::Warning << LP("CouldNotWriteFile", {Console::FileAdress(filename)}) << std::endl;
#endif
            throw(Error::TextFileWriteError);
        }
        return *this;
    }

    std::string& Text::operator>>(std::string& s)
    {
#ifdef DEBUG_READ_FILE
        std::cout << ConsoleBlocks::Debug << LP("ReadFromFile", {Console::FileAdress(filename)}) << std::endl;
#endif
        std::ifstream in(filename, std::ios::in | std::ios::binary);
        if (in)
        {
            in.seekg(0, std::ios::end);
            s.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&(s)[0], s.size());
            in.close();
        return s;
        }
#ifdef DEBUG_READ_FILE
        std::cout << ConsoleBlocks::Debug << ConsoleBlocks::Warning << LP("CouldNotReadFile", {Console::FileAdress(filename)}) << std::endl;
#endif
        throw(Error::TextFileReadError);
    }

    Folder Text::parent()
    {
        std::vector<std::string> vs = StringHelper::explode(filename, PATH_SLASH[0]);
        return *new Folder(__S__(filename).substr(0, __S__(filename).size()-vs.back().size()));
    }

    Text::~Text()
    {
        //fs.close();
    }
}
