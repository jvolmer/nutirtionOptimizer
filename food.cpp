#include "food.hpp"

Food::Food(const std::string& name, const std::vector<double>& nutritions, double min, double max, double cost):
    m_name {name},
    m_nutritionValues {nutritions},
    m_min {min},
    m_max {max},
    m_cost {cost}
{
    if (m_min > m_max)
    {
        double tmp = m_min;
        m_min = m_max;
        m_max = tmp;
    }
}

void Food::printAmount() const
{
    std::cout << m_name << "\t\t" << m_amount << " g" << std::endl;
}


bool operator== (const Food& lhs, const Food& rhs)
{
    bool compareNutritionValues = std::equal(lhs.m_nutritionValues.begin(), lhs.m_nutritionValues.end(), rhs.m_nutritionValues.begin(), specialFunctions::almostEqual);
    bool out = (
        ( lhs.m_name == rhs.m_name ) &&
        ( compareNutritionValues )
        );
    return out;
}

std::ostream& operator<< (std::ostream &out, const Food& food)
{
    out << food.m_name;
    out << ": { ";
    for(auto const& nutrition : food.m_nutritionValues)
        out << nutrition << " ";
    out << "}, ";
    out << "[ " << food.m_min << ", " << food.m_max << " ], ";
    out << food.m_cost;
    return out;
}

Json::Value Food::toJson() const
{
    Json::Value nutritionsOut;

    for (unsigned i=0; i<m_nutritionValues.size(); i++)
        nutritionsOut[std::to_string(i)] = m_nutritionValues[i];

    Json::Value foodOut;
    foodOut["name"] = m_name;
    foodOut["min"] = m_min;
    foodOut["max"] = m_max;
    foodOut["nutritions"] = nutritionsOut;

    return foodOut;
}

void Food::readFromJson(const Json::Value& foodObj)
{
    m_name = foodObj["name"].asString();

    m_nutritionValues.clear();
    const Json::Value& n = foodObj["nutritions"];
    for (unsigned i=0; i<n.size(); i++)
        m_nutritionValues.push_back(n[std::to_string(i)].asDouble());
    
    m_min = foodObj["min"].asDouble();
    m_max = foodObj["max"].asDouble();
}
