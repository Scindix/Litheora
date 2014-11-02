#include <include.h>

#ifndef CONFIGCOLUMNSTRING_H
#define CONFIGCOLUMNSTRING_H

#include <ConfigColumn.h>


class ConfigColumnSTRING : public ConfigColumn
{
    public:
        ConfigColumnSTRING(std::string n, bool in, bool id) : ConfigColumn::ConfigColumn(n, in, id){}
        virtual ~ConfigColumnSTRING();

        std::vector<size_t> selectEq(std::vector<std::string>);
        std::vector<size_t> selectEq(std::string);
        void add(std::vector<std::string>);
        void add(std::string);

        PROPERTY_TYPE type() const;
    protected:
    private:
        std::vector<std::string> cell;
};

#endif // CONFIGCOLUMNSTRING_H
