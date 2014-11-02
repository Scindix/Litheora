#ifndef STRINGHELPER_H
#define STRINGHELPER_H

#include <sstream>
#include <utility>
#include <vector>


namespace KeyWD
{
    static const std::vector<std::string> Parentheses = {"(", ")"};
    static const std::vector<std::string> Braces = {"{", "}"};
    static const std::vector<std::string> Chevrons = {"<", ">"};
    static const std::vector<std::string> Brackets = {"[", "]"};
    static const std::vector<std::string> Quotes = {"\"", "\""};
    static const std::vector<std::string> SingleQuotes = {"'", "'"};

    static const std::string Comma = ",";
    static const std::string Colon = ":";
    static const std::string SemiColon = ";";
    static const std::string Period = ".";
    static const std::string MinusSign = "-";
    static const std::string WeakEqual = ":";
    static const std::string Equal = "=";
    static const std::string PathSeperator = "/";
    static const std::string SpecialElement = "%";

    static const std::string Spaces = " \t\n\r";
    static const std::string Newline = "\n";

    static const std::string Numbers = "0123456789";
    static const std::string Chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
}

namespace std
{
    std::string to_string(std::string s);
}

class StringHelper
{
    public:
        StringHelper();
        virtual ~StringHelper();
        static std::vector<std::string> explode(std::string const & s, char delim);
        static bool replace(std::string&, const std::string, const std::string);
        static int replaceAll(std::string&, const std::string, const std::string);
        static std::string replaceR(std::string, const std::string, const std::string);
        static std::string replaceAllR(std::string, const std::string, const std::string);
        static unsigned int to_int_strict(std::string);
        static std::string blank(size_t);
        static std::string tab(size_t);
        static std::string nLine(size_t);
        static std::string gen(size_t, std::string);
        static std::string limit(size_t, std::string, std::string followerChars = " ...");
        static float toFloat(std::string);
        //static std::vector<std::string> parseFunction(std::string, std::vector<std::string>, std::string);
    protected:
    private:
};

#endif // STRINGHELPER_H
