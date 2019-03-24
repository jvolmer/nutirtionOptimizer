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
    double m_cost;
    double m_amount;
    
public:
    Food(const std::string& name, double min=0, double max=0, double cost=.5);
    Food(const std::string& name, const std::vector<double>& nutritions, double min=0, double max=0, double cost=.5);
    // Food(std::string foodString);
    friend bool operator== (const Food& lhs, const Food& rhs);

    std::string getName() const { return m_name; }
    double getMin() const { return m_min; }
    double getMax() const { return m_max; }
    const std::vector<double>& getNutritionValues() const { return m_nutritionValues; }
    double getCost() const { return m_cost; }
    double getAmount() const { return m_amount; }
    
    void setAmount(double amount){ m_amount = amount; }
    void printAmount() const;
};


#endif
