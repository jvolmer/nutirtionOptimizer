#ifndef STORE_H
#define STORE_H
#include <string>
#include <vector>
#include "food.hpp"

class Store{

private:
    std::string m_name;
    std::vector<Food> m_food;
    std::string m_fileName;

public:
    Store(std::string name, std::string fileName="");

    std::string getName(){ return m_name; }
    const std::vector<Food>& getFood(){ return m_food; }
    std::string getFileName(){ return m_fileName; }

    void addFood(Food& food);
    // void readFoodString();
    // void read();
    // void write();
};

#endif
