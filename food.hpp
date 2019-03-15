#ifndef FOOD_H
#define FOOD_H
#include <string>

class Food{

private:
    std::string m_name;
    std::string m_family;
    double m_carbonhydrateVal;
    double m_omega3Val;
    double m_ORACVal;

public:
    Food(std::string name, double carbonhydrateVal=0., double omega3Val=0., double ORACVal=0., std::string family="");

    void setNutritionValues(double carbohydrateVal=0., double omega3Val=0., double ORACVal=0.);
    std::string getName(){ return m_name; }
    std::string getFamily(){ return m_family; }
    double getCarbonhydrateValue(){ return m_carbonhydrateVal; }
};

#endif
