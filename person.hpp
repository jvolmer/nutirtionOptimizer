#ifndef PERSON_H
#define PERSON_H
#include <string>
#include "food.hpp"

class User
{
public:
    virtual ~User(){};
    virtual void setNutritionMinima(const std::vector<double>& nutrition) = 0;
    virtual const std::vector<double>& getNutritionMinima() const = 0;
};

class NutritionDemandingUser : public User
{    
private:
    std::string m_name;
    std::vector<double> m_nutritionMinimum;

public:
    NutritionDemandingUser(const std::string& name);
    NutritionDemandingUser(const std::string& name, const std::vector<double>& nutritionMinimum);

    const std::vector<double>& getNutritionMinima() const {return m_nutritionMinimum;}

    void setNutritionMinima(const std::vector<double>& nutrition){m_nutritionMinimum = nutrition;}
};

class MockUser : public User
{
private:
    std::vector<double> m_nutritionMinima{};
    
public:
    MockUser() {};
    ~MockUser() {};
    
    void setNutritionMinima(const std::vector<double>& nutrition) {};
    const std::vector<double>& getNutritionMinima() const { return m_nutritionMinima; };
};

#endif
