#ifndef STORE_H
#define STORE_H
#include <string>
#include <vector>
#include "food.hpp"
#include "person.hpp"
#include "solver.hpp"

class Stock{

public:
    virtual ~Stock() {};
    virtual std::string getName() const = 0;
    virtual std::string getLocation() const = 0;
    virtual const std::vector<Food>& getAllGoods() const = 0;
    virtual void addGood(const Food& food) = 0;
    // virtual void computeFoodPlan(const User& person) = 0;
};

class Store : public Stock {

private:
    std::string m_name;
    std::vector<Food> m_food;
    std::string m_location;

public:
    Store(const std::string& name, const std::string& location="");

    std::string getName() const { return m_name; }
    std::string getLocation() const { return m_location; }
    const std::vector<Food>& getAllGoods() const { return m_food; }

    void addGood(const Food& food){ m_food.push_back(food); }
    
    // void computeFoodPlan(const NutritionDemandingUser& person);

    // void readFoodString();
    // void read();
    // void write();
};

#endif
