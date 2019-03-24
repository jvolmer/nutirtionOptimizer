#ifndef STORE_H
#define STORE_H
#include <string>
#include <vector>
#include "food.hpp"
#include "person.hpp"
#include "solver.hpp"

class Store{

private:
    std::string m_name;
    std::vector<Food> m_food;
    std::string m_fileName;

public:
    Store(const std::string& name, const std::string& fileName="");

    std::string getName() const { return m_name; }
    const std::vector<Food>& getFood() const { return m_food; }
    std::string getFileName() const { return m_fileName; }

    void addFood(const Food& food){ m_food.push_back(food); }
    
    void computeFoodPlan(const Person& person);

    // void readFoodString();
    // void read();
    // void write();
};

#endif
