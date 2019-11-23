#ifndef BOUND_H
#define BOUND_H
#include <json/json.h>
#include <string>


class Bound
{
public:
    virtual ~Bound() {};
    virtual int getType() const = 0;
    virtual double getLower() const = 0;
    virtual double getUpper() const = 0;
    virtual Json::Value toJson() const = 0;
};

class GnuLinearBound : public Bound
{
private:
    int m_type;
    double m_lower;
    double m_upper;
    // static constexpr std::array<char[10], 5> boundName = {"GLP_FR", "GLP_LO", "GLP_UP", "GLP_DB", "GLP_FX"};
    
public:
    GnuLinearBound(double lower, double upper);
    GnuLinearBound init(double lower, double upper);
    int getType() const {return m_type;}
    double getLower() const {return m_lower;}
    double getUpper() const {return m_upper;}
    Json::Value toJson() const;
};


#endif
