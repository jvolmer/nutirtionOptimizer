#include "bound.hpp"
#include <glpk.h>
#include <limits>
#include <cmath>
#include <json/json.h>

GnuLinearBound::GnuLinearBound(double lower, double upper)
{
    if (std::isinf(lower) and std::isinf(upper))
        m_type = GLP_FR;
    else if (std::isinf(upper))
        m_type = GLP_LO;
    else if (std::isinf(lower))
        m_type = GLP_UP;
    else if (lower == upper)
        m_type = GLP_FX;

    else
        m_type = GLP_DB;

    if (std::isinf(lower))
        m_lower = 0;
    else
        m_lower = lower;
    
    if (std::isinf(upper))
        m_upper = 0;
    else
        m_upper = upper;
}


Json::Value GnuLinearBound::toJson() const
{
    std::array<std::string, 5> boundType{"GLP_FR", "GLP_LO", "GLP_UP", "GLP_DB", "GLP_FX"};
    Json::Value bound;
    bound["type"] = boundType[m_type-1];
    if (m_type == GLP_FR || m_type == GLP_UP)
        bound["lower"] = -std::numeric_limits<double>::infinity();
    else
        bound["lower"] = m_lower;
    if (m_type == GLP_FR || m_type == GLP_LO)
        bound["upper"] = std::numeric_limits<double>::infinity();
    else
        bound["upper"] = m_upper;
    return bound;
}
