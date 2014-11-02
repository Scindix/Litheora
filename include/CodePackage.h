#ifndef CODEPACKAGE_H
#define CODEPACKAGE_H

#include <string>

class CodePackage
{
    public:
        CodePackage();
        CodePackage(size_t* i, std::string* s, size_t* l, std::string n);
        void parse(size_t* i, std::string* s, size_t* l, std::string n);
        virtual ~CodePackage();
        std::string name;
    protected:
    private:
};

#endif // CODEPACKAGE_H
