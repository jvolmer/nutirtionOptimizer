#include "food.hpp"

Food::Food(std::string name, double carbonhydrateVal, double omega3Val, double ORACVal, std::string family):
    m_name {name},
    m_family {family},
    m_carbonhydrateVal {carbonhydrateVal},
    m_omega3Val {omega3Val},
    m_ORACVal {ORACVal}
{
}

