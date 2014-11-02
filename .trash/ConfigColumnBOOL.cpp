#include "ConfigColumnBOOL.h"

ConfigColumnBOOL::~ConfigColumnBOOL()
{
    //dtor
}

std::vector<size_t> ConfigColumnBOOL::selectEq(std::vector<bool> vi)
{
    std::vector<size_t> out;
    size_t c = 0;
    for(const bool &item: cell)
    {
        for(const bool &comp: vi)
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

std::vector<size_t> ConfigColumnBOOL::selectEq(bool i)
{
    std::vector<size_t> out;
    size_t c = 0;
    for(const bool &item: cell)
    {
        if(item == i)
            out.push_back(c);
        c++;
    }
    return out;
}

void ConfigColumnBOOL::add(std::vector<bool> vi)
{
    cell.insert(cell.end(), vi.begin(), vi.end());
}

void ConfigColumnBOOL::add(bool i)
{
    cell.push_back(i);
}

PROPERTY_TYPE ConfigColumnBOOL::type() const
{
    return PropertyType::BOOL;
}
