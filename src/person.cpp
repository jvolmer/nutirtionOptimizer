#include "person.hpp"
#include <json/json.h>
#include <vector>
#include <string>
#include <utility>

NutritionDemandingUser::NutritionDemandingUser(std::string name, std::vector<double> nutritionMinimum, std::vector<double> nutritionMaximum):
    m_name {std::move(name)},
    m_nutritionMinimum {std::move(nutritionMinimum)},
    m_nutritionMaximum {std::move(nutritionMaximum)}
{
}

Json::Value NutritionDemandingUser::toJson() const
{
    Json::Value nutritionMinima;
    for (unsigned i=0; i<m_nutritionMinimum.size(); i++)
        nutritionMinima[std::to_string(i)] = m_nutritionMinimum[i];

    Json::Value nutritionMaxima;
    for (unsigned i=0; i<m_nutritionMaximum.size(); i++)
        nutritionMaxima[std::to_string(i)] = m_nutritionMaximum[i];

    Json::Value personOut;
    personOut["name"] = m_name;
    personOut["nutritionMinima"] = nutritionMinima;
    personOut["nutritionMaxima"] = nutritionMaxima;

    return personOut;
}

void NutritionDemandingUser::readFromJson(const Json::Value& personObj)
{
    m_name = personObj["name"].asString();
    
    m_nutritionMinimum.clear();
    m_nutritionMaximum.clear();
    
    const Json::Value& nMin = personObj["nutritionMinima"];
    for (unsigned i=0; i<nMin.size(); i++)
        m_nutritionMinimum.push_back(nMin[std::to_string(i)].asDouble());

    const Json::Value& nMax = personObj["nutritionMaxima"];
    for (unsigned i=0; i<nMax.size(); i++)
        m_nutritionMinimum.push_back(nMax[std::to_string(i)].asDouble());

}
