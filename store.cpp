#include "store.hpp"

FoodStore::FoodStore(const std::string& name, const std::string& location):
    m_name {name},
    m_location {location}
{
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
