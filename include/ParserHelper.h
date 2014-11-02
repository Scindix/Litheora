#ifndef PARSERHELPER_H
#define PARSERHELPER_H

#include <debug.h>
#include <StringHelper.h>

class ConfigSection;

class ParserHelper
{
    public:
        ParserHelper();
        virtual ~ParserHelper();

        static void skipSpaces(size_t*, std::string*, size_t*);
        static std::string getString(size_t*, std::string*, size_t*, std::string followerChars = "\"");
        static std::string getWord(size_t*, std::string*, size_t*, std::string followerChars = "");
        static void* getNumber(bool*, size_t*, std::string*, size_t*);
        static bool getBool(size_t*, std::string*, size_t*);
        static ConfigSection* getSection(size_t*, std::string*, size_t*, std::string);
    protected:
    private:
};

#endif // PARSERHELPER_H
