#ifndef CONFIGSECTION_H
#define CONFIGSECTION_H

//#include <include.h>
#include <Property.h>

class ConfigSection
{
    public:
        ConfigSection();
        virtual ~ConfigSection();
        bool parse(std::string*, size_t*, size_t*);
        Property& at(std::string);
        Property& atParam(std::string);
        Property& operator/(std::string);
        std::string name;
        std::vector<Property> param;
        std::vector<Property> prop;
    protected:
    private:
};

#endif // CONFIGSECTION_H
