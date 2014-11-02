#include <include.h>

#ifndef CONFIGCOLUMNINT_H
#define CONFIGCOLUMNINT_H

#include <ConfigColumn.h>


class ConfigColumnINT : public ConfigColumn
{
    public:
        ConfigColumnINT(std::string n, bool in, bool id) : ConfigColumn::ConfigColumn(n, in, id){}
        virtual ~ConfigColumnINT();

        std::vector<size_t> selectEq(std::vector<int>);
        std::vector<size_t> selectEq(int);
        void add(std::vector<int>);
        void add(int);

        PROPERTY_TYPE type() const;
    protected:
    private:
        std::vector<int> cell;
};

#endif // CONFIGCOLUMNINT_H
