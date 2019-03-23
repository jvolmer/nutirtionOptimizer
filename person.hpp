#ifndef PERSON_H
#define PERSON_H
#include <string>
#include "food.hpp"

class Person{

private:
    std::string m_name;
    Food m_foodMinimum;

public:
    Person(std::string name);
    Person(std::string name, const Food& foodMinimum);
};

#endif
