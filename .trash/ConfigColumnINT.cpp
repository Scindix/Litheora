#include "ConfigColumnINT.h"

ConfigColumnINT::~ConfigColumnINT()
{
    //dtor
}

std::vector<size_t> ConfigColumnINT::selectEq(std::vector<int> vi)
{
    std::vector<size_t> out;
    size_t c = 0;
    for(const int &item: cell)
    {
        for(const int &comp: vi)
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

std::vector<size_t> ConfigColumnINT::selectEq(int i)
{
    std::vector<size_t> out;
    size_t c = 0;
    for(const int &item: cell)
    {
        if(item == i)
            out.push_back(c);
        c++;
    }
    return out;
}

void ConfigColumnINT::add(std::vector<int> vi)
{
    cell.insert(cell.end(), vi.begin(), vi.end());
}

void ConfigColumnINT::add(int i)
{
    cell.push_back(i);
}

PROPERTY_TYPE ConfigColumnINT::type() const
{
    return PropertyType::INT;
}

