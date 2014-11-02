#include "Property.h"
#include "ConfigTable.h"
#include "ConfigSection.h"
//#include "StringHelper.h"

Property::Property()
{
    m_name = "";
    m_value = nullptr;
    m_type = PropertyType::VOID;
}

Property::~Property()
{

}

Property::Property(std::string n, int v)
{
    m_name = n;
    m_value = (void*)&v;
    m_type = PropertyType::INT;
}

Property::Property(std::string n, double v)
{
    m_name = n;
    m_value = (void*)&v;
    m_type = PropertyType::DOUBLE;
}

Property::Property(std::string n, std::string v)
{
    m_name = n;
    m_value = (void*)&v;
    m_type = PropertyType::STRING;
}

Property::Property(std::string n, ConfigSection& v)
{
    m_name = n;
    m_value = (void*)&v;
    m_type = PropertyType::LIST;
}

Property::Property(std::string n, CodePackage& c)
{
    m_name = n;
    m_value = (void*)&c;
    m_type = PropertyType::CODE;
}

void Property::name(std::string n)
{
    m_name = n;
}

std::string Property::name()
{
    return m_name;
}

void* Property::value()
{
    return m_value;
}

void Property::setValue(void* v)
{
    m_value = v;
}

std::string Property::valueSTRING()
{
    if(m_type == PropertyType::STRING)
        return __S__((const char*)m_value);
    else
        throw(Error::ConfigTypesNotMatch);
}

int Property::valueINT()
{
    if(m_type == PropertyType::INT)
        return *((int*)m_value);
    else
        throw(Error::ConfigTypesNotMatch);
}

double Property::valueDOUBLE()
{
    if(m_type == PropertyType::DOUBLE)
        return *((double*)m_value);
    else
        throw(Error::ConfigTypesNotMatch);
}

bool Property::valueBOOL()
{
    if(m_type == PropertyType::BOOL)
        return *((bool*)m_value);
    else
        throw(Error::ConfigTypesNotMatch);
}

ConfigSection& Property::valueLIST()
{
    if(m_type == PropertyType::LIST)
        return *((ConfigSection*)m_value);
    else
        throw(Error::ConfigTypesNotMatch);
}

ConfigTable* Property::valueTABLE()
{
    if(m_type == PropertyType::TABLE)
        return ((ConfigTable*)m_value);
    else
        throw(Error::ConfigTypesNotMatch);
}

CodePackage* Property::valueCODE()
{
    if(m_type == PropertyType::CODE)
        return ((CodePackage*)m_value);
    else
        throw(Error::ConfigTypesNotMatch);
}

char Property::type()
{
    return m_type;
}

std::string Property::getString()
{
    switch(m_type)
    {
    case PropertyType::VOID:
        return __S__("null");
    case PropertyType::INT:
        return std::to_string(valueINT());
    case PropertyType::DOUBLE:
        return std::to_string(valueDOUBLE());
    case PropertyType::STRING:
        return __S__("\"") + valueSTRING() + __S__("\"");
    case PropertyType::BOOL:
        return valueBOOL()?__S__("true"):__S__("false");
    case PropertyType::BITMASK:
        return __S__("BITMASK");
    case PropertyType::CODE:
        return valueCODE()->name;
    case PropertyType::TABLE:
        return __S__("(") + valueTABLE()->printHeader() + __S__(")");
    case PropertyType::LIST:
        ConfigSection cs = valueLIST();
        std::string out("(");
        for(size_t i = 0; i < (size_t)std::min((int)cs.prop.size(), 3); i++)
            out += cs.prop[i].getString() + __S__(", ");
        out += "...)";
        return out;
    }
    return __S__("null");
}

std::string Property::getSaveString()
{
    switch(m_type)
    {
    case PropertyType::VOID:
        return __S__();
    case PropertyType::DOUBLE:
        return m_name + KeyWD::WeakEqual + std::to_string(valueDOUBLE()) + ";";
    case PropertyType::INT:
        return m_name + KeyWD::WeakEqual + std::to_string(valueINT()) + ";";
    case PropertyType::STRING:
        return m_name + KeyWD::WeakEqual + __S__("\"") + valueSTRING() + "\";";
    case PropertyType::BOOL:
        return m_name + KeyWD::WeakEqual + getString() + ";";
    case PropertyType::TABLE:
        return m_name + KeyWD::WeakEqual + valueTABLE()->print() + ";";
    case PropertyType::LIST:
        std::string out = m_name + KeyWD::WeakEqual + __S__("{");
        ConfigSection cs = valueLIST();
        for(size_t i = 0; i < cs.prop.size(); i++)
            out += cs.prop[i].getSaveString() + __S__(" ");
        out += __S__("};");
        return out;
    }
    return __S__();
}

std::string Property::getStatusString(char c)
{
    switch(c)
    {
    case PropertyType::VOID:
        return __S__("VOID");
    case PropertyType::INT:
        return __S__("INT");
    case PropertyType::DOUBLE:
        return __S__("DOUBLE");
    case PropertyType::STRING:
        return __S__("STRING");
    case PropertyType::LIST:
        return __S__("LIST");
    case PropertyType::BOOL:
        return __S__("BOOL");
    case PropertyType::BITMASK:
        return __S__("BITMASK");
    case PropertyType::TABLE:
        return __S__("TABLE");
    case PropertyType::CODE:
        return __S__("CODEPACKAGE");
    default:
        return __S__("UNKNOWN");
    }
}

//#define DEBUG_PARSE_PROPERTY
bool Property::parse(std::string* line, size_t* initial, char stop, size_t* lineNumber, const std::string equalSign)
{
    if(initial == nullptr)
        initial = new size_t(0);
    std::string name("");
    try
    {
        ParserHelper::skipSpaces(initial, line, lineNumber);
    } catch_err(Error::ParserEOF, Error::ConfigSectionUnclosed)

    if(line->at(*initial)==stop)
    {
        *initial = ++(*initial);
        return false;
    }

    try
    {
        name = ParserHelper::getWord(initial, line, lineNumber, equalSign);
    } catch_err2(Error::ParserEOF, Error::ConfigStatementUnclosed,
                 Error::ParserStringWordUnrecognizedChar, Error::ConfigUnrecognizedCharL)

    try
    {
        ParserHelper::skipSpaces(initial, line, lineNumber);
    } catch_err(Error::ParserEOF, Error::ConfigStatementUnclosed)

    if(line->at(*initial)==equalSign[0])
        (*initial)++;
    else
        throw(Error::ConfigMissingWeakEqual);

    try
    {
        ParserHelper::skipSpaces(initial, line, lineNumber);
    } catch_err(Error::ParserEOF, Error::ConfigStatementUnclosed)

    if(line->at(*initial)=='"')
    {
        try
        {
            std::string value = ParserHelper::getString(initial, line, lineNumber);
            m_name = name;
            m_value = (void*)__S__(value).c_str();
            m_type = PropertyType::STRING;
        } catch_err(Error::ParserStringMissingEnd, Error::ConfigMissingStringEnd)

    } else if(KeyWD::Numbers.find(line->at(*initial))!=std::string::npos || line->at(*initial) == '-')
    {
        bool* type = new bool(false);
        void* num = ParserHelper::getNumber(type, initial, line, lineNumber);
        m_name = name;
        m_value = num;
        if(*type)
        {
            m_type = PropertyType::INT;
        } else
        {
            m_type = PropertyType::DOUBLE;
        }
        delete type;
    } else if(line->substr(*initial, 4)== "true" || line->substr(*initial, 5)== "false")
    {
        m_name = name;
        bool boolVal = ParserHelper::getBool(initial, line, lineNumber);
        m_value = new bool(boolVal);
        m_type = PropertyType::BOOL;
    } else if(line->at(*initial)=='{')
    {
        m_name = name;
        ConfigSection* cs = ParserHelper::getSection(initial, line, lineNumber, name);
        m_value = cs;
        m_type = PropertyType::LIST;
    } else if(line->at(*initial)=='(')
    {
        m_name = name;
        ConfigTable* ct = new ConfigTable();
        ct->parse(line, initial, ')', lineNumber);
        m_value = ct;
        m_type = PropertyType::TABLE;
    }
    else
        throw(Error::ConfigUnrecognizedCharR);
    while(true)
    {
#ifdef DEBUG_PARSE_PROPERTY
        std::cout << "\tsearching empty characters (to the end of line)\n";
#endif // DEBUG_PARSE_PROPERTY
        if(*initial >= line->size() || line->at(*initial)==stop)
            throw(Error::ConfigStatementUnclosed);
        if(line->at(*initial)==' ' || line->at(*initial)=='\t' || line->at(*initial)=='\n' || line->at(*initial)=='\r')
        {
            if(line->at(*initial)=='\n')
                (*lineNumber)++;
            (*initial)++;
        }
        else if(line->at(*initial)==';')
        {
            *initial = (*initial)+1;
            return true;
        }
        else
        {
            throw(Error::ConfigUnrecognizedCharRFSemi);
        }
    }
}
