#include "ConfigColumnTemplate.h"

template <class Value, PROPERTY_TYPE pt>
ConfigColumnTemplate<Value, pt>::~ConfigColumnTemplate<Value, pt>()
{
    //dtor
}

template <class Value, PROPERTY_TYPE pt>
std::vector<size_t> ConfigColumnTemplate<Value, pt>::selectEq(std::vector<Value> vi)
{
    std::vector<size_t> out;
    size_t c = 0;
    for(const Value &item: cell)
    {
        for(const Value &comp: vi)
        {
            if(item == comp)
            {
                out.push_back(c);
                break;
            }
        }
        c++;
    }
    return out;
}

template <class Value, PROPERTY_TYPE pt>
std::vector<size_t> ConfigColumnTemplate<Value, pt>::selectEq(Value i)
{
    std::vector<size_t> out;
    size_t c = 0;
    for(const Value &item: cell)
    {
        if(item == i)
            out.push_back(c);
        c++;
    }
    return out;
}

template <class Value, PROPERTY_TYPE pt>
void ConfigColumnTemplate<Value, pt>::add(std::vector<Value> vi)
{
    cell.insert(cell.end(), vi.begin(), vi.end());
}

template <class Value, PROPERTY_TYPE pt>
void ConfigColumnTemplate<Value, pt>::add(Value i)
{
    cell.push_back(i);
}

template <class Value, PROPERTY_TYPE pt>
void ConfigColumnTemplate<Value, pt>::preserve(size_t i)
{
    cell.insert(cell.end(), i, standardVal);
}

template <class Value, PROPERTY_TYPE pt>
Value ConfigColumnTemplate<Value, pt>::getCell(size_t i)
{
    return cell[i];
}

template <class Value, PROPERTY_TYPE pt>
PROPERTY_TYPE ConfigColumnTemplate<Value, pt>::type() const
{
    return pt;
}

template <class Value, PROPERTY_TYPE pt>
std::string ConfigColumnTemplate<Value, pt>::stdValue() const
{
    return valToString(standardVal);
}

template <class Value, PROPERTY_TYPE pt>
size_t ConfigColumnTemplate<Value, pt>::size() const
{
    return cell.size();
}

template <class Value, PROPERTY_TYPE pt>
std::string ConfigColumnTemplate<Value, pt>::printCell(size_t i) const
{
    return valToString(cell[i]);
}

template <class Value, PROPERTY_TYPE pt>
std::string ConfigColumnTemplate<Value, pt>::print() const
{
    std::string out;
    std::string pre("");
    if(m_identity)
        pre = "@";
    if(m_increment)
        pre+= "+";

    out += S("auto ")+(pre + m_name + "=") + (valToString(standardVal) + ",\t");
    return out.substr(0, out.size()-2);
}

template <class Value, PROPERTY_TYPE pt>
std::string ConfigColumnTemplate<Value, pt>::valToString(Value v) const
{
    return std::to_string(v);
}

template <>
std::string ConfigColumnTemplate<std::string, PropertyType::STRING>::valToString(std::string v) const
{
    return S("\"") + v + "\"";
}

template <>
std::string ConfigColumnTemplate<bool, PropertyType::BOOL>::valToString(bool v) const
{
    if(v)
        return S("true");
    else
        return S("false");
}

///tell the compiler to explicitly compile the 'bool', 'string', 'int' and 'double' versions of 'ConfigColumn'
template class ConfigColumnTemplate<bool, PropertyType::BOOL>;
template class ConfigColumnTemplate<std::string, PropertyType::STRING>;
template class ConfigColumnTemplate<int, PropertyType::INT>;
template class ConfigColumnTemplate<double, PropertyType::DOUBLE>;
