#include <include.h>

#ifndef CODEPACKAGEPATH_H
#define CODEPACKAGEPATH_H


class CodePackagePath
{
    public:
        CodePackagePath();
        CodePackagePath(size_t*, std::string*, size_t*);
        virtual ~CodePackagePath();
        void parse(size_t*, std::string*, size_t*);
        CodePackagePath& operator+(CodePackagePath);
        bool beginsAtRoot;
        std::string name;
        std::vector<std::string> children;
    protected:
    private:
};

#endif // CODEPACKAGEPATH_H
