#include "person.hpp"

NutritionDemandingUser::NutritionDemandingUser(const std::string& name):
    m_name {name}
{
}

NutritionDemandingUser::NutritionDemandingUser(const std::string& name, const std::vector<double>& nutritionMinimum):
    m_name {name},
    m_nutritionMinimum {nutritionMinimum}
{
}
