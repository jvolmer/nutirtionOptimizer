#include "person.hpp"

Person::Person(std::string name):
    m_name {name},
    m_foodMinimum {"foodMinimum"}
{
}

Person::Person(std::string name, const Food& foodMinimum):
    m_name {name},
    m_foodMinimum {foodMinimum}
{
}
