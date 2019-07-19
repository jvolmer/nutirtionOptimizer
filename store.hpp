#ifndef STORE_H
#define STORE_H
#include "food.hpp"
#include <json/json.h>
#include <string>
#include <vector>
#include <utility>

class Store
{
public:
    virtual ~Store() {};
    virtual std::string getName() const = 0;
    virtual unsigned getNumberOfNutritions() const = 0;
    virtual unsigned getNumberOfFoods() const = 0;
    // virtual std::vector<std::reference_wrapper<Food>> getAllGoodReferences() const = 0;
    virtual std::vector<double> getFoodPropertyVector(std::string property) const = 0;
    virtual std::vector<std::vector<double>> getFoodNutritionValues() const = 0;

    virtual bool containsFoodAtPosition(int i, const Food& foodToCompare) const = 0;

    virtual void addGood(Food good) = 0;
    virtual void clearFood() = 0;

    virtual void decorateWithCost(const std::vector<double>& newVariableVector) = 0;
    virtual void decorateWithAmount(const std::vector<double>& newVariableVector) = 0;

    virtual std::vector<double> computeOptimizedTotalNutritions() = 0;

    virtual void readFromJson(const Json::Value& storeObj) = 0;
    virtual Json::Value toJson() const = 0;
};

class FoodStore : public Store
{
private:
    std::string m_name;
    std::vector<std::unique_ptr<Food>> m_food;

public:
    FoodStore(std::string name=""); //, std::vector<std::unique_ptr<Food>> nutritions={});

    std::string getName() const { return m_name; }
    unsigned getNumberOfNutritions() const;
    unsigned getNumberOfFoods() const { return m_food.size(); }
    // std::vector<std::reference_wrapper<Food>> getAllGoodReferences() const;
    std::vector<double> getFoodPropertyVector(std::string property) const;
    std::vector<std::vector<double>> getFoodNutritionValues() const;
    
    bool containsFoodAtPosition(int i, const Food& foodToCompare) const
    { return *m_food[i] == foodToCompare; }
    
    void addGood(Food food){ m_food.push_back(std::make_unique<Food>(std::move(food))); }
    void addGood(std::unique_ptr<Food> food){ m_food.push_back(std::move(food)); }
    void clearFood(){ m_food.clear(); }

    void decorateWithCost(const std::vector<double>& newVariableVector);
    void decorateWithAmount(const std::vector<double>& newVariableVector);

    std::vector<double> computeOptimizedTotalNutritions();
    
    void readFromJson(const Json::Value& storeObj);
    Json::Value toJson() const;
};

class MockStore : public Store
{
private:
    std::vector<Food> m_good;
    
public:
    MockStore() {};
    ~MockStore() {};
    
    std::string getName() const { return ""; };
    unsigned getNumberOfNutritions() const {if (m_good.size()==0) return 0; else return m_good[0].getNumberOfNutritions();}
    unsigned getNumberOfFoods() const { return m_good.size(); }
    // std::vector<std::reference_wrapper<Food>> getAllGoodReferences() const {return {};}
    std::vector<double> getFoodPropertyVector(std::string property) const { return {}; }
    std::vector<std::vector<double>> getFoodNutritionValues() const {return {}; }
    
    bool containsFoodAtPosition(int i, const Food& foodToCompare) const
    { return m_good[i] == foodToCompare; }

    void addGood(Food good){}; // m_good.push_back(std::move(good)); };
    void clearFood(){ m_good.clear(); }

    void decorateWithCost(const std::vector<double>& newVariableVector){};
    void decorateWithAmount(const std::vector<double>& newVariableVector){};

    std::vector<double> computeOptimizedTotalNutritions(){return {};}

    void readFromJson(const Json::Value& storeObj) {};
    Json::Value toJson() const { return Json::Value{}; };
};


#endif
