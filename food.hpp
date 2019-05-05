#ifndef FOOD_H
#define FOOD_H
#include <string>
#include <vector>
#include <iostream>
#include <json/json.h>
#include "specialFunctions.hpp"

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
    virtual Json::Value toJson() const = 0;
    virtual void readFromJson(const Json::Value& foodObj) = 0;
    
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
    Food(std::string name="", std::vector<double> nutritions={}, double min=0, double max=0, double cost=.5);
     
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

    void setName(const std::string& name) {};
    void setAmount(double amount) {};
    void printAmount() const {};
    Json::Value toJson() const {return Json::Value{};}
    void readFromJson(const Json::Value& foodObj) {};
};

#endif
