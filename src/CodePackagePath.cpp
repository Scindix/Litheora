#include "CodePackagePath.h"

CodePackagePath::CodePackagePath()
{
    //ctor
}

CodePackagePath::CodePackagePath(std::string s)
{
    parse(s);
}

CodePackagePath::~CodePackagePath()
{
    //dtor
}

void parse(size_t* i, std::string* s, size_t* lineNumber)
{
    ParserHelper::skipSpaces(i, s, lineNumber);
    beginsAtRoot = ((*s)[*i] == KeyWD::PathSeperator[0])
    if(beginsAtRoot) (*i)++;
    while(1)
    {
        bool special = false;
        if((*s)[*i] == KeyWD::SpecialElement[0])
        {
            special = true;
            (*i)++;
        }
        std::string s = ParserHelper::getWord(i, s, lineNumber, "%");
        if(special)
        {
            if((*s)[*i] != KeyWD::SpecialElement[0])
                throw(Error::ConfigWrongCodePath);
            (*i)++;
            s = S("%") + s + "%";
        }
        children.push_back(s);
        if((*s)[*i] != KeyWD::PathSeperator[0])
        {
            if()
        }
    }
}

CodePackagePath& operator+(CodePackagePath c)
{
    CodePackagePath out(*this);
    out.children.insert(out.children.end(), c.children.begin(), c.children.end());
    return out;
}
