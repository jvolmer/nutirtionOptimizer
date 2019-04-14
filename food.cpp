#include <iostream>
#include "food.hpp"

Food::Food():
    m_name {""},
    m_min {0},
    m_max {0},
    m_cost {0}
{
}

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

void Food::printAmount() const
{
    std::cout << m_name << "\t\t" << m_amount << " g" << std::endl;
}

bool operator== (const Food& lhs, const Food& rhs)
{
    bool out = ( (lhs.m_name == rhs.m_name) && (lhs.m_nutritionValues == rhs.m_nutritionValues) );
    return out;
}

std::ostream& operator<< (std::ostream &out, const Food& food)
{
    out << food.m_name << ": ( ";
    for(auto const& nutrition : food.m_nutritionValues)
        out << nutrition << " ";
    out << ")";
    return out;
}
