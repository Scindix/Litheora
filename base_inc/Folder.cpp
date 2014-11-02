#include "Folder.h"

namespace File
{
    Folder::Folder()
    {
        init(PATH_ROOT);
    }

    Folder::~Folder()
    {
        //dtor
    }

    Folder::Folder(std::string p)
    {
        init(p);
    }

    Folder::Folder(std::string p, std::string appBase)
    {
        if(appBase.substr(0, PATH_SLASH.size()) == PATH_SLASH)
            appBase = appBase.substr(1);
        if(appBase.substr(appBase.size()-PATH_SLASH.size(), PATH_SLASH.size()) != PATH_SLASH)
            appBase = appBase + PATH_SLASH;
        std::string ppath;
        if(p.substr(0, PATH_SLASH.size()+1) == "." + PATH_SLASH)
            ppath = APP.basePath + PATH_SLASH + appBase + p.substr(2);
        else if(p.substr(0, PATH_ROOT.size()) != PATH_ROOT)
            ppath = APP.basePath + PATH_SLASH + p;
        else
            ppath = p;
        init(ppath);
    }

    Folder::Folder(std::string p, Folder appBase)
    {
        std::string ppath;
        if(p.substr(0, PATH_SLASH.size()+1) == "." + PATH_SLASH)
            ppath = APP.basePath + appBase.getPath() + p.substr(2);
        else if(p.substr(0, PATH_ROOT.size()) != PATH_ROOT)
            ppath = APP.basePath + PATH_SLASH + p;
        else
            ppath = p;
        init(ppath);
    }

    std::string Folder::getPath()
    {
        std::string out = PATH_ROOT;
        for(std::string name : pathNames)
        {
            out += name + PATH_SLASH;
        }
        return out;
    }

    void Folder::init(std::string p)
    {
        DIR *dir = opendir(p.c_str());
        if(dir == NULL)
            throw(Error::DirOpenError);
        else
        {
            path = p;
            pathNames = StringHelper::explode(p, PATH_SLASH[0]);
            name = pathNames.back();
        }
    }

    Folder& Folder::operator=(const char* p)
    {
        init(__S__(p));
        return *this;
    }

    Folder& Folder::operator=(std::string p)
    {
        init(p);
        return *this;
    }

    Folder& Folder::enter(std::string f)
    {
        try
        {
            init(path + PATH_SLASH + f);
        } catch(Exception e)
        {
            if(e == Error::DirOpenError)
                throw(Error::DirEnterError);
            else
                throw(e);
        }
        return *this;
    }

    Folder& Folder::up()
    {
        std::vector<std::string> pathNames = StringHelper::explode(path, PATH_SLASH[0]);
        std::string newDir = path.substr(0, path.size()-pathNames.back().size()-1);
        try
        {
            init(newDir);
        } catch(Exception e)
        {
            if(e == Error::DirOpenError)
                throw(Error::DirUpError);
            else
                throw(e);
        }
        return *this;
    }

    std::vector<std::string> Folder::files()
    {
        std::vector<std::string> out;
        DIR *dir;
        struct dirent *ent;
        if((dir = opendir (path.c_str())) != NULL)
        {
            while((ent = readdir (dir)) != NULL)
            {
                if(!(ent->d_type & DT_DIR))
                {
                    out.push_back(__S__(ent->d_name));
#ifdef DEBUG_FOLDER
                    std::cout << ConsoleBlocks::Debug << "Folder found:" << ent->d_name << "\n";/**@todo implement language support in Folder class: LP("FolderFound", {__S__(ent->d_name)}) << "\n";**/
                } else
                {
                    std::cout << ConsoleBlocks::Debug << "File found:" << ent->d_name << "\n";

                }
#else
                }
#endif
            }
            closedir(dir);
        } else
            throw(Error::DirOpenError);
        return out;
    }

    std::vector<Folder> Folder::folders()
    {
        std::vector<Folder> out;
        DIR *dir;
        struct dirent *ent;
        if((dir = opendir (path.c_str())) != NULL)
        {
            while((ent = readdir (dir)) != NULL)
            {
                if((ent->d_type & DT_DIR) && __S__(ent->d_name)!=__S__(".") && __S__(ent->d_name)!=__S__(".."))
                {
                    Folder add(path + PATH_SLASH + ent->d_name);
                    out.push_back(add);
#ifdef DEBUG_FOLDER
                    std::cout << ConsoleBlocks::Debug << "Folder found:" << ent->d_name << "\n";
                } else
                {
                    std::cout << ConsoleBlocks::Debug << "File found:" << ent->d_name << "\n";

                }
#else
                }
#endif
            }
            closedir(dir);
        } else
            throw(Error::DirOpenError);
        return out;
    }
}
