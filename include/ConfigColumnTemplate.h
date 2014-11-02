#include <include.h>

#ifndef CONFIGCOLUMNTEMPLATE_H
#define CONFIGCOLUMNTEMPLATE_H


#include <ConfigColumn.h>



template <class Value, PROPERTY_TYPE pt> class ConfigColumnTemplate : public ConfigColumn
{
    public:
        ConfigColumnTemplate(std::string n, bool in, bool id, Value stdVal) : ConfigColumn::ConfigColumn(n, in, id), standardVal(stdVal){}
        virtual ~ConfigColumnTemplate();

        std::vector<size_t> selectEq(std::vector<Value>);
        std::vector<size_t> selectEq(Value);
        void add(std::vector<Value>);
        void add(Value);
        void preserve(size_t);

        Value getCell(size_t);

        PROPERTY_TYPE type() const;
        std::string stdValue() const;

        std::string printCell(size_t) const;
        std::string print() const;
        size_t size() const;
        std::string valToString(Value) const;
    protected:
    private:
        Value standardVal;
        std::vector<Value> cell;
};

typedef ConfigColumnTemplate<bool, PropertyType::BOOL>              ConfigColumnBOOL;
typedef ConfigColumnTemplate<std::string, PropertyType::STRING>     ConfigColumnSTRING;
typedef ConfigColumnTemplate<int, PropertyType::INT>                ConfigColumnINT;
typedef ConfigColumnTemplate<double, PropertyType::DOUBLE>          ConfigColumnDOUBLE;

#endif // CONFIGCOLUMNTEMPLATE_H
