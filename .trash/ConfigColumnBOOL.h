#include <include.h>

#ifndef CONFIGCOLUMNBOOL_H
#define CONFIGCOLUMNBOOL_H

#include <ConfigColumn.h>


class ConfigColumnBOOL : public ConfigColumn
{
    public:
        ConfigColumnBOOL(std::string n, bool in, bool id) : ConfigColumn::ConfigColumn(n, in, id), , standardVal(false){}
        ConfigColumnBOOL(std::string n, bool in, bool id, bool stdVal) : ConfigColumn::ConfigColumn(n, in, id), standardVal(stdVal){}
        virtual ~ConfigColumnBOOL();

        std::vector<size_t> selectEq(std::vector<bool>);
        std::vector<size_t> selectEq(bool);
        void add(std::vector<bool>);
        void add(bool);
        void preseve(int);

        PROPERTY_TYPE type() const;
    protected:
    private:
        bool standardVal;
        std::vector<bool> cell;
};

#endif // CONFIGCOLUMNBOOL_H
