#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <vector>
#include <string>
#include <dirent.h>
#include <Console.h>
#include <StringHelper.h>
#include <error.h>
#include <preprocessor.h>
//#include <Language.h>

#ifdef _WIN32
#define PATH_ROOT (*new std::string("C:\\"))
#define PATH_SLASH (*new std::string("\\"))
#else
#define PATH_ROOT (*new std::string("/"))
#define PATH_SLASH (*new std::string("/"))
#endif

namespace File
{
    class Folder
    {
        public:
            Folder();
            Folder(std::string);
            Folder(std::string, std::string);
            Folder(std::string, Folder);
            void init(std::string);
            Folder& operator=(const char*);
            Folder& operator=(std::string);
            std::vector<Folder> folders();
            std::vector<std::string> files();
            Folder& enter(std::string);
            Folder& up();
            std::string name;
            std::string path;
            std::string getPath();
            std::vector<std::string> pathNames;
            virtual ~Folder();
        protected:
        private:
    };
}


#endif // FILESYSTEM_H
