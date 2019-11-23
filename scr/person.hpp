#ifndef PERSON_H
#define PERSON_H
#include <json/json.h>
#include <vector>
#include <string>

class User
{
public:
    virtual ~User(){};
    virtual void setNutritionMinima(const std::vector<double>& nutrition) = 0;
    virtual void setNutritionMaxima(const std::vector<double>& nutrition) = 0;
    virtual const std::vector<double>& getNutritionMinima() const = 0;
    virtual const std::vector<double>& getNutritionMaxima() const = 0;
    virtual Json::Value toJson() const = 0;
    virtual void readFromJson(const Json::Value& personObj) = 0;
};

class NutritionDemandingUser : public User
{    
private:
    std::string m_name;
    std::vector<double> m_nutritionMinimum;
    std::vector<double> m_nutritionMaximum;

public:
    NutritionDemandingUser(std::string name="", std::vector<double> nutritionMinimum={}, std::vector<double> nutritionMaximum={});

    const std::vector<double>& getNutritionMinima() const {return m_nutritionMinimum;}
    const std::vector<double>& getNutritionMaxima() const {return m_nutritionMaximum;}

    void setNutritionMinima(const std::vector<double>& nutrition){m_nutritionMinimum = nutrition;}
    void setNutritionMaxima(const std::vector<double>& nutrition){m_nutritionMaximum = nutrition;}

    Json::Value toJson() const;
    void readFromJson(const Json::Value& personObj);
};

class MockUser : public User
{
private:
    std::vector<double> m_nutritionMinimum;
    std::vector<double> m_nutritionMaximum;
    
public:
    MockUser() {};
    ~MockUser() {};
    
    void setNutritionMinima(const std::vector<double>& nutrition){m_nutritionMinimum = nutrition;}
    void setNutritionMaxima(const std::vector<double>& nutrition){m_nutritionMaximum = nutrition;}
    const std::vector<double>& getNutritionMinima() const { return m_nutritionMinimum; };
    const std::vector<double>& getNutritionMaxima() const { return m_nutritionMaximum; };

    Json::Value toJson() const { return Json::Value{}; };
    void readFromJson(const Json::Value& personObj) {};
};

#endif
