#include "store.hpp"

Store::Store(std::string name, std::string fileName):
    m_name {name},
    m_fileName {fileName}
{
}

void Store::addFood(const Food& food)
{
    m_food.push_back(food);
}
