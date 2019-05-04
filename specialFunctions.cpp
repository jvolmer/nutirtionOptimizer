#include "specialFunctions.hpp"

bool specialFunctions::almostEqual(const double& left, const double& right)
{
    return (fabs(left - right) < 1E-10);
}
