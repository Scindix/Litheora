#include <include.h>

#ifndef CONFIGCOLUMNDOUBLE_H
#define CONFIGCOLUMNDOUBLE_H

#include <ConfigColumn.h>


class ConfigColumnDOUBLE : public ConfigColumn
{
    public:
        ConfigColumnDOUBLE(std::string n, bool in, bool id) : ConfigColumn::ConfigColumn(n, in, id){}
        virtual ~ConfigColumnDOUBLE();

        std::vector<size_t> selectEq(std::vector<double>);
        std::vector<size_t> selectEq(double);
        void add(std::vector<double>);
        void add(double);

        PROPERTY_TYPE type() const;
    protected:
    private:
        std::vector<double> cell;
};

#endif // CONFIGCOLUMNDOUBLE_H
