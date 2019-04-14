#ifndef FOOD_H
#define FOOD_H
#include <string>
#include <vector>

class Good{

public:
    virtual ~Good() {};
    virtual std::string getName() const = 0;
    virtual double getMin() const = 0;
    virtual double getMax() const = 0;
    virtual const std::vector<double>& getNutritionValues() const = 0;
    virtual double getCost() const = 0;
    virtual double getAmount() const = 0;

    virtual void setName(const std::string& name) = 0;
    
    virtual void setAmount(double amount) = 0;
    virtual void printAmount() const = 0;    
    
};

class Food : public Good {

private:
    std::string m_name;
    std::vector<double> m_nutritionValues;
    double m_min;
    double m_max;
    double m_cost;
    double m_amount;
    
public:
    Food();
    Food(const std::string& name, double min=0, double max=0, double cost=.5);
    Food(const std::string& name, const std::vector<double>& nutritions, double min=0, double max=0, double cost=.5);
    // Food(std::string foodString);
    friend bool operator== (const Food& lhs, const Food& rhs);
    friend std::ostream& operator<< (std::ostream &out, const Food& food);

    std::string getName() const { return m_name; }
    double getMin() const { return m_min; }
    double getMax() const { return m_max; }
    const std::vector<double>& getNutritionValues() const { return m_nutritionValues; }
    double getCost() const { return m_cost; }
    double getAmount() const { return m_amount; }

    void setName(const std::string& name){ m_name = name; }
    
    void setAmount(double amount){ m_amount = amount; }
    void printAmount() const;
};


#endif
