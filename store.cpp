#include "store.hpp"

FoodStore::FoodStore(const std::string& name, const std::string& location):
    m_name {name},
    m_location {location}
{
}

void FoodStore::read()
{
    std::ifstream infile(m_location);

    Json::Value fileContent;
    infile >> fileContent;

    for (const Json::Value& foodObj : fileContent)
    {
        Food food;
        food.readFromJson(foodObj);
        addGood(std::move(food));
    }
}

void FoodStore::write()
{
    std::ofstream outfile(m_location);

    Json::Value input;
    
    for (const Food& food : m_food)
        input.append(food.toJson());

    outfile << input;
}
