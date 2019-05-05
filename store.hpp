#ifndef STORE_H
#define STORE_H
#include <string>
#include <vector>
#include <fstream>
#include <json/json.h>
#include "food.hpp"

class Store{

public:
    virtual ~Store() {};
    virtual std::string getName() const = 0;
    virtual const std::vector<Food>& getAllGoods() const = 0;
    virtual void addGood(Food good) = 0;
    
    virtual void readFromJson(const Json::Value& storeObj) = 0;
    virtual Json::Value toJson() const = 0;
};

class FoodStore : public Store {

private:
    std::string m_name;
    std::vector<Food> m_food;

public:
    FoodStore(std::string name="", std::vector<Food> nutritions={});

    std::string getName() const { return m_name; }
    const std::vector<Food>& getAllGoods() const { return m_food; }

    void addGood(Food food){ m_food.push_back(std::move(food)); }
    void clearFood(){ m_food.clear(); }

    void readFromJson(const Json::Value& storeObj);
    Json::Value toJson() const;
};

class MockStore : public Store{

private:
    std::vector<Food> m_good;
    
public:
    MockStore() {};
    ~MockStore() {};
    
    std::string getName() const { return ""; };
    const std::vector<Food>& getAllGoods() const { return m_good; }
    void addGood(Food good){ m_good.push_back(std::move(good)); };
    
    void readFromJson(const Json::Value& storeObj) {};
    Json::Value toJson() const { return Json::Value{}; };
};


#endif
