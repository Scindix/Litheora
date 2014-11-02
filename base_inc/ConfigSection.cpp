#include "ConfigSection.h"

ConfigSection::ConfigSection()
{
    //ctor
}

ConfigSection::~ConfigSection()
{
    //dtor
}

Property& ConfigSection::operator/(std::string s)
{
    return at(s);
}

Property& ConfigSection::at(std::string p)
{
    for(size_t i = 0; i < prop.size(); i++)
    {
        if(prop[i].name() == p)
            return prop[i];
    }
    throw(Error::ConfigAtSearchPropNotFound);
}

Property& ConfigSection::atParam(std::string p)
{
    for(size_t i = 0; i < param.size(); i++)
    {
        if(param[i].name() == p)
            return param[i];
    }
    throw(Error::ConfigAtSearchPropNotFound);
}

bool ConfigSection::parse(std::string* line, size_t* initial, size_t* lineNumber)
{
    std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
    std::string numbers = "0123456789";
    name = "";
    try
    {
        ParserHelper::skipSpaces(initial, line, lineNumber);
    } catch(Exception e)
    {
        if(e == Error::ParserEOF)
            return false;
        else
            throw(e);
    }
    try
    {
        name = ParserHelper::getWord(initial, line, lineNumber, KeyWD::Braces[0]+KeyWD::Brackets[0]);
    } catch(Exception e)
    {
        if(e == Error::ParserEOF)
            throw(Error::ConfigStatementUnclosed);
        else if(e == Error::ParserStringWordUnrecognizedChar)
        {
            std::cout << ConsoleBlocks::Info << "Conflicting char: '" << line->at(*initial) << "'\n";
            throw(Error::ConfigUnrecognizedSectionName);
        }
    }

    try
    {
        ParserHelper::skipSpaces(initial, line, lineNumber);
    } catch_err(Error::ParserEOF, Error::ConfigStatementUnclosed)
    bool hasParams = true;
    if(line->substr(*initial, 1) == KeyWD::Brackets[0])
    {
        (*initial)++;
    }
    else if(line->substr(*initial, 1) == KeyWD::Braces[0])
    {
        hasParams = false;
        (*initial)++;
    }
    else
        throw(Error::ConfigUnrecognizedSectionParam);

    if(hasParams)
    {
        while(true)
        {
            Property p;
            try
            {
                if(p.parse(line, initial, KeyWD::Brackets[1][0], lineNumber, KeyWD::Equal))
                {
                    param.push_back(p);
                }
                else
                    break;
            } catch_auto
        }
        try
        {
            ParserHelper::skipSpaces(initial, line, lineNumber);
        } catch_err(Error::ParserEOF, Error::ConfigStatementUnclosed)

        if(line->substr(*initial, 1) == KeyWD::Braces[0])
            (*initial)++;
        else
            throw(Error::ConfigUnrecognizedSectionParamEnd);
    }

    while(true)
    {
        Property p;
        if(p.parse(line, initial, KeyWD::Braces[1][0], lineNumber))
        {
    #ifdef DEBUG_PARSE_CONFIG_SECTION
            std::cout << ConsoleBlocks::Debug << "Parsing line " << *lineNumber << ", name=\"" << p.name() << "\"\n";
    #endif
            prop.push_back(p);
        }
        else
        {
            return true;
        }
    }
}
