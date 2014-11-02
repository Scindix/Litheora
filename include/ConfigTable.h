#ifndef CONFIGTABLE_H
#define CONFIGTABLE_H

#include <ParserHelper.h>

#include "ConfigColumns.h"


class ConfigTable
{
    public:
        ConfigTable();
        ConfigTable(const ConfigTable&);
        virtual ~ConfigTable();
        std::vector<ConfigColumn*> column;
        ConfigTable select(ConfigColumnItem, std::string);
        ConfigColumnItem select(ConfigColumnItem);
        void parse(std::string*, size_t*, char, size_t*);
        size_t selectColumn(std::string);
        std::string printHeader();
        std::string print();
    protected:
    private:
        ConfigColumn* UIDC;
        template <class ColumnType, class stdVal>
            void addColumn(std::string, bool, bool, stdVal);
};

#endif // CONFIGTABLE_H
