#ifndef FOOD_H
#define FOOD_H
#include <string>
#include <vector>
#include <iostream>
#include <json/json.h>
#include "specialFunctions.hpp"

enum class InputType{
    JSON
};

class Good{

public:
    virtual ~Good() {};
    virtual std::string getName() const = 0;
    virtual double getMin() const = 0;
    virtual double getMax() const = 0;
    virtual const std::vector<double>& getNutritionValues() const = 0;
    virtual double getCost() const = 0;
    virtual double getAmount() const = 0;
    virtual unsigned getNumberOfNutritions() const = 0;

    virtual void setName(const std::string& name) = 0;
    
    virtual Json::Value toJson() const = 0;
    virtual void readFromJson(const Json::Value& foodObj) = 0;
    
};

class Food : public Good {

private:
    std::string m_name;
    std::vector<double> m_nutritionValues;
    double m_min;
    double m_max;
    
public:
    Food(std::string name="", std::vector<double> nutritions={}, double min=0, double max=0);
    Food(const Food& food);
    Food(InputType inputType, const Json::Value& jsonObject);
    ~Food() {};
    
    friend bool operator== (const Food& lhs, const Food& rhs);
    friend std::ostream& operator<< (std::ostream &out, const Food& food);

    std::string getName() const { return m_name; }
    double getMin() const { return m_min; }
    double getMax() const { return m_max; }
    const std::vector<double>& getNutritionValues() const { return m_nutritionValues; }
    double getCost() const { return -1; }
    double getAmount() const { return -1; }
    unsigned getNumberOfNutritions() const { return m_nutritionValues.size(); }
    
    void setName(const std::string& name){ m_name = name; }    
    
    Json::Value toJson() const;
    void readFromJson(const Json::Value& foodObj);
};

class MockGood : public Good{

private:
    std::vector<double> m_nutritionValues{};
public:
    MockGood() {};
    ~MockGood() {};
    
    std::string getName() const {return "";}
    double getMin() const {return 0;}
    double getMax() const {return 0;}
    const std::vector<double>& getNutritionValues() const {return m_nutritionValues;}
    double getCost() const {return 0;}
    double getAmount() const {return 0;}
    unsigned getNumberOfNutritions() const {return m_nutritionValues.size();}
    
    void setName(const std::string& name) {};

    Json::Value toJson() const {return Json::Value{};}
    void readFromJson(const Json::Value& foodObj) {};
};

// Decorator

class FoodDecorator : public Food
{
public:
    virtual ~FoodDecorator() {};
};

class Amount : public FoodDecorator
{
private:
    std::unique_ptr<Food> m_food;
    double m_amount;
public:
    Amount(std::unique_ptr<Food> food, double amount=0.);
    ~Amount() {};

    double getAmount() const { return m_amount; }
    double getCost() const { return m_food->getCost(); }
    double getMin() const {return m_food->getMin(); }
    double getMax() const {return m_food->getMax(); }
    const std::vector<double>& getNutritionValues() const { return m_food->getNutritionValues(); }
    unsigned getNumberOfNutritions() const { return m_food->getNumberOfNutritions(); }

    void setName(const std::string& name){ m_food->setName(name); }

    Json::Value toJson() const;
    void readFromJson(const Json::Value& jsonObject);
};

class Cost : public FoodDecorator
{
private:
    std::unique_ptr<Food> m_food;
    double m_cost;
public:
    Cost(std::unique_ptr<Food> food, double cost=0.);
    ~Cost() {};

    double getAmount() const {return m_food->getAmount(); }
    double getCost() const { return m_cost; }
    double getMin() const {return m_food->getMin(); }
    double getMax() const {return m_food->getMax(); }
    const std::vector<double>& getNutritionValues() const { return m_food->getNutritionValues(); }
    unsigned getNumberOfNutritions() const { return m_food->getNumberOfNutritions(); }

    void setName(const std::string& name){ m_food->setName(name); }
    
    Json::Value toJson() const;
    void readFromJson(const Json::Value& jsonObject);
};

#endif
