#ifndef FOOD_H
#define FOOD_H
#include <string>
#include <vector>

class Food{

private:
    std::string m_name;
    std::vector<double> m_nutritionValues;
    double m_min;
    double m_max;

public:
    Food(std::string name, double min=0, double max=0);
    Food(std::string name, const std::vector<double>& nutritions, double min=0, double max=0);
    // Food(std::string foodString);
    friend bool operator== (const Food& lhs, const Food& rhs);

    std::string getName(){ return m_name; }
    double getMin(){ return m_min; }
    double getMax(){ return m_max; }
    const std::vector<double>& getNutritionValues(){ return m_nutritionValues; }

    // std::string getString();
};


#endif
