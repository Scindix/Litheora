#include "CodePackage.h"

CodePackage::CodePackage()
{
    //ctor
}

CodePackage::~CodePackage()
{
    //dtor
}

CodePackage::CodePackage(size_t* i, std::string* s, size_t* l, std::string n)
{
    parse(i, s, l, n);
}

void CodePackage::parse(size_t* i, std::string* s, size_t* l, std::string n)
{
    name = n;
}
