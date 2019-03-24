#include "person.hpp"

Person::Person(const std::string& name):
    m_name {name}
{
}

Person::Person(const std::string& name, const std::vector<double>& nutritionMinimum):
    m_name {name},
    m_nutritionMinimum {nutritionMinimum}
{
}
