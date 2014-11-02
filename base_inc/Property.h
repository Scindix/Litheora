#ifndef PROPERTY_H
#define PROPERTY_H

//#include <include.h>
#include <string>
#include <vector>
#include "error.h"
#include "platform.h"
#include <ParserHelper.h>
#include <stdlib.h>
#include <PROPERTY_TYPE.h>
#include <CodePackage.h>


#define __S__(s) (*new std::string(s))

class ConfigSection;
class ConfigTable;

class Property
{
    public:
        Property();
        Property(std::string, int);
        Property(std::string, double);
        Property(std::string, std::string);
        Property(std::string, ConfigSection&);
        Property(std::string, CodePackage&);
        bool parse(std::string*, size_t*, char, size_t*, const std::string = KeyWD::WeakEqual);
        virtual ~Property();
        std::string name();
        void name(std::string);
        void* value();
        std::string valueSTRING();
        int valueINT();
        double valueDOUBLE();
        bool valueBOOL();
        ConfigTable* valueTABLE();
        ConfigSection& valueLIST();
        CodePackage* valueCODE();
        void setValue(void*);
        std::string getString();
        std::string getSaveString();
        char type();
        static std::string getStatusString(char);
    protected:
    private:
        void* m_value;
        std::string m_name;
        PROPERTY_TYPE m_type;
};

#endif // PROPERTY_H
