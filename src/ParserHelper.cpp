#include "ParserHelper.h"
#include <ConfigSection.h>

ParserHelper::ParserHelper()
{
    //ctor
}

ParserHelper::~ParserHelper()
{
    //dtor
}

ConfigSection* ParserHelper::getSection(size_t* initial, std::string* line, size_t* lineNumber, std::string name)
{
#ifdef DEBUG_PARSERHELPER
        std::cout << "\tsection\t pos='" << *initial << "'; char='" << line->at(*initial) << "'\n";
#endif // DEBUG_PARSERHELPER
    std::string l = name + line->substr(*initial);
    size_t* count = new size_t(0);
    ConfigSection* cs = new ConfigSection();
    cs->parse(&l, count, lineNumber);
    *initial += *count - name.size();
    delete count;
    return cs;
}

bool ParserHelper::getBool(size_t* initial, std::string* line, size_t* lineNumber)
{
#ifdef DEBUG_PARSERHELPER
        std::cout << "\tbool\t pos='" << *initial << "'; char='" << line->at(*initial) << "'\n";
#endif // DEBUG_PARSERHELPER
    bool b = line->substr(*initial, 4) == "true";
    *initial += 4;
    if(!b)
        (*initial)++;
    return b;
}

void* ParserHelper::getNumber(bool* nType, size_t* initial, std::string* line, size_t* lineNumber)
{
    std::string f = "";
    bool positive = true;
    if(line->at(*initial) == '-')
    {
        positive = false;
        (*initial)++;
    }
    bool comma = true;
    while(true)
    {
#ifdef DEBUG_PARSERHELPER
        std::cout << "\tnumber\t pos='" << *initial << "'; char='" << line->at(*initial) << "'\n";
#endif // DEBUG_PARSERHELPER
        if(KeyWD::Numbers.find(line->at(*initial))!=std::string::npos || (comma && line->at(*initial)=='.'))
        {
            f.push_back(line->at(*initial));
            if(line->at(*initial)=='.')
                comma = false;
            (*initial)++;
        }
        else break;
    }
    if(comma)
    {
        *nType = true;

        int* fS = new int((positive?1:-1)*atoi(f.c_str()));
        return (void*)fS;
    } else
    {
        *nType = false;
        double* fS = new double((positive?1:-1)*atof(f.c_str()));
        return (void*)fS;
    }
}

std::string ParserHelper::getString(size_t* initial, std::string* line, size_t* lineNumber, std::string followerChars)
{
    size_t endTag;
    size_t posOffset = *initial;
    while(true)
    {
#ifdef DEBUG_PARSERHELPER
        std::cout << "\tsearching closing quote: pos='" << *initial << "'; char='" << line->at(*initial) << "'\n";
#endif // DEBUG_PARSERHELPER
        endTag = line->find(followerChars, posOffset+1);
        if(endTag == std::string::npos)
            throw(Error::ParserStringMissingEnd);
        if(line->at(endTag-1) != '\\')
            break;
        else
            posOffset++;
    }
    std::string value = line->substr(*initial+1, endTag-(*initial+1));
    StringHelper::replaceAll(value, "\\n", "\n");
    StringHelper::replaceAll(value, "\\t", "\t");
    StringHelper::replaceAll(value, "\\v", "\v");
    StringHelper::replaceAll(value, "\\\"", "\"");
    StringHelper::replaceAll(value, "\\a", "\a");
    StringHelper::replaceAll(value, "\\b", "\b");
    StringHelper::replaceAll(value, "\\\\", "\\");

    *initial = ++endTag;
    return value;
}

std::string ParserHelper::getWord(size_t* initial, std::string* line, size_t* lineNumber, std::string followerChars)
{
    bool first = true;
    std::string name;
    while(true)
    {
#ifdef DEBUG_PARSERHELPER
        std::cout << "\tparsing word string\t pos='" << *initial << "'; char='" << line->at(*initial) << "'\n";
#endif // DEBUG_PARSERHELPER
        if(*initial >= line->size())
            throw(Error::ParserEOF);
        if((!first && KeyWD::Numbers.find(line->at(*initial))!=std::string::npos) || (KeyWD::Chars.find(line->at(*initial))!=std::string::npos))
        {
            name.push_back(line->at(*initial));
            (*initial)++;
        }
        else if((KeyWD::Spaces + followerChars).find(line->at(*initial)) != std::string::npos)
            return name;
        else
            throw(Error::ParserStringWordUnrecognizedChar);
        first = false;
    }
}

void ParserHelper::skipSpaces(size_t* initial, std::string* line, size_t* lineNumber)
{
    while(true)
    {
#ifdef DEBUG_PARSERHELPER
        std::cout << "\tsearching empty characters\t pos='" << *initial << "'; char='" << line->at(*initial) << "'\n";
#endif // DEBUG_PARSERHELPER
        if(*initial >= line->size())
            throw(Error::ParserEOF);

        if(KeyWD::Spaces.find(line->at(*initial)) != std::string::npos)
        {
            if(line->at(*initial)==KeyWD::Newline[0])
                (*lineNumber)++;
            (*initial)++;
        }
        else
        {
            return;
        }
    }
}
