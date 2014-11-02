#include "ConfigColumnSTRING.h"

ConfigColumnSTRING::~ConfigColumnSTRING()
{
    //dtor
}

std::vector<size_t> ConfigColumnSTRING::selectEq(std::vector<std::string> vi)
{
    std::vector<size_t> out;
    size_t c = 0;
    for(const std::string &item: cell)
    {
        for(const std::string &comp: vi)
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

std::vector<size_t> ConfigColumnSTRING::selectEq(std::string i)
{
    std::vector<size_t> out;
    size_t c = 0;
    for(const std::string &item: cell)
    {
        if(item == i)
            out.push_back(c);
        c++;
    }
    return out;
}

void ConfigColumnSTRING::add(std::vector<std::string> vi)
{
    cell.insert(cell.end(), vi.begin(), vi.end());
}

void ConfigColumnSTRING::add(std::string i)
{
    cell.push_back(i);
}

PROPERTY_TYPE ConfigColumnSTRING::type() const
{
    return PropertyType::STRING;
}


