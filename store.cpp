#include "store.hpp"

FoodStore::FoodStore(std::string name, std::vector<Food> foods):
    m_name {std::move(name)},
    m_food {std::move(foods)}
{
}

int FoodStore::getNumberOfNutritions() const
{
    if (m_food.size() == 0)
        return 0;
    else
        return m_food[0].getNumberOfNutritions();
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
    for (const Food& food : m_food)
        foods.append(food.toJson());
    
    Json::Value storeObj;
    storeObj["name"] = m_name;
    storeObj["foods"] = foods;

    return storeObj;
}
