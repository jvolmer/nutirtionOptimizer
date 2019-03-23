#include "store.hpp"

Store::Store(std::string name, std::string fileName):
    m_name {name},
    m_fileName {fileName}
{
}

void Store::addFood(Food& food)
{
    m_food.push_back(food);
}
