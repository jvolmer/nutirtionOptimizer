#include "food.hpp"

Food::Food(const std::string& name, const std::vector<double>& nutritions, double min, double max, double cost):
    m_name {name},
    m_nutritionValues {nutritions},
    m_min {min},
    m_max {max},
    m_cost {cost}
{
    if (m_min > m_max)
    {
        double tmp = m_min;
        m_min = m_max;
        m_max = tmp;
    }    
}

Food::Food(const std::string& name, double min, double max, double cost):
    m_name {name},
    m_min {min},
    m_max {max},
    m_cost {cost}
{
    if (m_min > m_max)
    {
        double tmp = m_min;
        m_min = m_max;
        m_max = tmp;
    }    
}

bool operator== (const Food& lhs, const Food& rhs)
{
    bool out = ( (lhs.m_name == rhs.m_name) && (lhs.m_min == rhs.m_min) && (lhs.m_max == rhs.m_max) && (lhs.m_nutritionValues == rhs.m_nutritionValues) );
    return out;
}
