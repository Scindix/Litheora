#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <iostream>
#include "error.h"
#include <string>
#include <Folder.h>

namespace File
{
    enum FileOperator
    {
        Erase = 0,
        EraseLastLine,
    };

    class Text
    {
        public:
            Text();
            Text(std::string);
            Text(std::string, std::string);
            Text(std::string, Folder);
            Text(const char*);
            virtual ~Text();
            void operator=(std::string);
            void operator=(const char*);
            void load(std::string);
            void load(const char*);
            Text& operator<<(std::string&);
            std::string& operator>>(std::string&);
            Folder parent();
            const char* filename;
        protected:
        private:
            void open();
            void close();
    };

}

//std::string get_file_contents(const char *filename);
#endif // FILE_H
