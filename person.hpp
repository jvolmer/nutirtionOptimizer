#ifndef PERSON_H
#define PERSON_H
#include <string>
#include "food.hpp"

class Person{

private:
    std::string m_name;
    std::vector<double> m_nutritionMinimum;

public:
    Person(const std::string& name);
    Person(const std::string& name, const std::vector<double>& nutritionMinimum);

    const std::vector<double>& getNutritionMinima() const {return m_nutritionMinimum;}
};

#endif
