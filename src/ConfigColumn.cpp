
#include "ConfigColumn.h"

ConfigColumn::ConfigColumn(std::string s, bool inc, bool id)
{
    m_name = s;
    m_increment = inc;
    m_identity = id;
}

std::string ConfigColumn::name() const
{
    return m_name;
}

bool ConfigColumn::increment() const
{
    return m_increment;
}

bool ConfigColumn::identity() const
{
    return m_identity;
}

