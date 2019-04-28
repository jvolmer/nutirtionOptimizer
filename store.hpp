#ifndef STORE_H
#define STORE_H
#include <string>
#include <vector>
#include "food.hpp"

template <class T>
class Stock{

public:
    virtual ~Stock() {};
    virtual std::string getName() const = 0;
    virtual std::string getLocation() const = 0;
    virtual const std::vector<T>& getAllGoods() const = 0;
    virtual void addGood(const T& good) = 0;
};

class Store : public Stock<Food> {

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
    
    // void readFoodString();
    // void read();
    // void write();
};

class MockStock : public Stock<MockGood>{

private:
    std::vector<MockGood> m_good;
    
public:
    MockStock() {};
    ~MockStock() {};
    
    std::string getName() const { return ""; };
    std::string getLocation() const { return ""; };
    const std::vector<MockGood>& getAllGoods() const { return m_good; }
    void addGood(const MockGood& good) { m_good.push_back(good); }
};


#endif
