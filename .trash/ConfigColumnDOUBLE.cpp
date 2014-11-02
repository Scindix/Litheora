#include "ConfigColumnDOUBLE.h"

ConfigColumnDOUBLE::~ConfigColumnDOUBLE()
{
    //dtor
}

std::vector<size_t> ConfigColumnDOUBLE::selectEq(std::vector<double> vi)
{
    std::vector<size_t> out;
    size_t c = 0;
    for(const double &item: cell)
    {
        for(const double &comp: vi)
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

std::vector<size_t> ConfigColumnDOUBLE::selectEq(double i)
{
    std::vector<size_t> out;
    size_t c = 0;
    for(const double &item: cell)
    {
        if(item == i)
            out.push_back(c);
        c++;
    }
    return out;
}

void ConfigColumnDOUBLE::add(std::vector<double> vi)
{
    cell.insert(cell.end(), vi.begin(), vi.end());
}

void ConfigColumnDOUBLE::add(double i)
{
    cell.push_back(i);
}

PROPERTY_TYPE ConfigColumnDOUBLE::type() const
{
    return PropertyType::DOUBLE;
}
