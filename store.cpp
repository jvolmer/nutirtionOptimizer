#include "store.hpp"

FoodStore::FoodStore(std::string name): //, std::vector<Food> foods):
    m_name {std::move(name)}
    // m_food {std::move(foods)}
{
}

int FoodStore::getNumberOfNutritions() const
{
    if (m_food.size() == 0)
        return 0;
    else
        return m_food[0]->getNumberOfNutritions();
}

void FoodStore::decorateWithCost(const std::vector<double>& newVariableVector)
{
    if (newVariableVector.size() == getNumberOfNutritions())
        for (unsigned i=0; i<newVariableVector.size(); i++)
            m_food[i] = std::make_unique<Cost>(std::move(m_food[i]), newVariableVector[i]);
}

void FoodStore::decorateWithAmount(const std::vector<double>& newVariableVector)
{
    if (newVariableVector.size() == getNumberOfNutritions())
        for (unsigned i=0; i<newVariableVector.size(); i++)
            m_food[i] = std::make_unique<Amount>(std::move(m_food[i]), newVariableVector[i]);
}

void FoodStore::readFromJson(const Json::Value& storeObj)
{
    m_name = storeObj["name"].asString();

    clearFood();
    const Json::Value& foods = storeObj["foods"];
    for (const Json::Value& foodObj : foods)
    {
        Food food;
        food.readFromJson(foodObj);
        addGood(std::move(food));
    }
}

Json::Value FoodStore::toJson() const
{
    Json::Value foods;
    for (const auto& food : m_food)
        foods.append(food->toJson());
    
    Json::Value storeObj;
    storeObj["name"] = m_name;
    storeObj["foods"] = foods;

    return storeObj;
}
