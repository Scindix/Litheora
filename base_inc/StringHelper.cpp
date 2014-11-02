#include "StringHelper.h"
#include <error.h>

#define S__(s) (*new std::string(s))

StringHelper::StringHelper()
{
    //ctor
}

StringHelper::~StringHelper()
{
    //dtor
}

bool StringHelper::replace(std::string& haystack, const std::string needle, const std::string replacement)
{
    size_t start_pos = haystack.find(needle);
    if(start_pos == std::string::npos)
        return false;
    haystack.replace(start_pos, needle.length(), replacement);
    return true;
}

std::string StringHelper::blank(size_t s)
{
    return gen(s, S__(" "));
}

std::string StringHelper::nLine(size_t s)
{
    return gen(s, S__("\n"));
}

std::string StringHelper::tab(size_t s)
{
    return gen(s, S__("\t"));
}

std::string StringHelper::gen(size_t s, std::string in)
{
    std::string out;
    for(size_t i = 0; i < s; i++)
        out += in;
    return out;
}

int StringHelper::replaceAll(std::string& haystack, const std::string needle, const std::string replacement)
{
    if(needle.empty())
        return 0;
    size_t start_pos = 0;
    unsigned int replacements = 0;
    while((start_pos = haystack.find(needle, start_pos)) != std::string::npos)
    {
        replacements++;
        haystack.replace(start_pos, needle.length(), replacement);
        start_pos += replacement.length();
    }
    return replacements;
}

std::string StringHelper::replaceR(std::string haystack, const std::string needle, const std::string replacement)
{
    std::string output(haystack);
    size_t start_pos = output.find(needle);
    if(start_pos == std::string::npos)
        return output;
    output.replace(start_pos, needle.length(), replacement);
    return output;
}

std::string StringHelper::replaceAllR(std::string haystack, const std::string needle, const std::string replacement)
{
    std::string output(haystack);
    if(needle.empty())
        return output;
    size_t start_pos = 0;
    while((start_pos = output.find(needle, start_pos)) != std::string::npos)
    {
        output.replace(start_pos, needle.length(), replacement);
        start_pos += replacement.length();
    }
    return output;
}

std::vector<std::string> StringHelper::explode(std::string const & s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim); )
    {
        result.push_back(std::move(token));
    }

    return result;
}

unsigned int StringHelper::to_int_strict(std::string intStr)
{
    for(size_t i = 0; i < intStr.size(); i++)
    {
        if(KeyWD::Numbers.find(intStr.at(i)) == std::string::npos)
        {
            throw(Error::StringToIntStrictUnrecognizedChar);
        }
    }
    if(intStr.size() == 0)
    {
        return 0;
    }
    return std::stoi(intStr);
}

std::string StringHelper::limit(size_t n, std::string s, std::string followerChars)
{
    if(s.size() > n)
    {
        return s.substr(0, n-followerChars.size()) + followerChars;
    } else
        return s;
}

float StringHelper::toFloat(std::string s)
{
    std::stringstream sstr;
    sstr<<s;
    float f;
    sstr>>f;
    return f;
}

/*std::vector<std::string> StringHelper::parseFunction(std::string haystack, std::vector<std::string> brackets, std::string delim)
{
    size_t left = haystack.find(brackets[0]);
    size_t right = haystack.find(brackets[1]);
    size_t pos = 0;
    if(left==std::string::npos)
    {
        if(right!=std::string::npos)
            throw(Error::MissingBracketBegin);
        else
        {
            std::vector<std::string> out = {haystack};
            return out;
        }
    } else
    {
        left = haystack.find(brackets[0], left);
        ///if()
    }
}*/

#undef S__

namespace std
{
    std::string to_string(std::string s)
    {
        return s;
    }
}
