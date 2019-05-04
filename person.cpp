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

Json::Value NutritionDemandingUser::toJson() const
{
    Json::Value nutritions;
    
    for (unsigned i=0; i<m_nutritionMinimum.size(); i++)
        nutritions[std::to_string(i)] = m_nutritionMinimum[i];

    Json::Value personOut;
    personOut["name"] = m_name;
    personOut["nutritionMinima"] = nutritions;

    return personOut;
}

void NutritionDemandingUser::readFromJson(const Json::Value& personObj)
{
    m_name = personObj["name"].asString();
    
    m_nutritionMinimum.clear();
    const Json::Value& n = personObj["nutritionMinima"];
    for (unsigned i=0; i<n.size(); i++)
        m_nutritionMinimum.push_back(n[std::to_string(i)].asDouble());
    
}
