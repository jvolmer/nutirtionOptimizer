#ifndef STORE_H
#define STORE_H
#include <string>
#include <vector>
#include "food.hpp"

class Store{

public:
    virtual ~Store() {};
    virtual std::string getName() const = 0;
    virtual std::string getLocation() const = 0;
    virtual const std::vector<Food>& getAllGoods() const = 0;
    virtual void addGood(const Food& good) = 0;
};

class FoodStore : public Store {

private:
    std::string m_name;
    std::vector<Food> m_food;
    std::string m_location;

public:
    FoodStore(const std::string& name, const std::string& location="");

    std::string getName() const { return m_name; }
    std::string getLocation() const { return m_location; }
    const std::vector<Food>& getAllGoods() const { return m_food; }

    void addGood(const Food& food){ m_food.push_back(food); }
    
    // void readFoodString();
    // void read();
    // void write();
};

class MockStore : public Store{

private:
    std::vector<Food> m_good;
    
public:
    MockStore() {};
    ~MockStore() {};
    
    std::string getName() const { return ""; };
    std::string getLocation() const { return ""; };
    const std::vector<Food>& getAllGoods() const { return m_good; }
    void addGood(const Food& good) { m_good.push_back(good); }
};


#endif
