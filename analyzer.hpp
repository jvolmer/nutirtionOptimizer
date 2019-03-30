#ifndef ANALYZER_H
#define ANALYZER_H
#include "store.hpp"
#include "person.hpp"
#include "solver.hpp"
#include "food.hpp"

class Analyzer{

private:
    const Store& m_store;
    const NutritionDemandingUser& m_person;
    std::vector<double> m_foodAmount;

public:
    Analyzer(const Store& store, const NutritionDemandingUser& person);

    const std::vector<double>& getAmounts() const { return m_foodAmount; } 
    void computeFoodPlan();
};

#endif
    
