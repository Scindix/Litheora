#ifndef CONFIGCOLUMN_H
#define CONFIGCOLUMN_H

#include "ConfigColumnItem.h"
#include <PROPERTY_TYPE.h>


class ConfigColumn
{
    public:
        ConfigColumn(std::string s, bool inc, bool id);

        std::string name() const;
        bool increment() const;
        bool identity() const;
        virtual PROPERTY_TYPE type() const = 0;
        virtual size_t size() const = 0;
        virtual std::string stdValue() const = 0;
        virtual std::string printCell(size_t) const = 0;
        virtual std::string print() const = 0;
    protected:
        std::string m_name;
        bool m_increment;
        bool m_identity;
    private:
};

#endif // CONFIGCOLUMN_H
