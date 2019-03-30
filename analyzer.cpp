#include "analyzer.hpp"

Analyzer::Analyzer(const Store& store, const NutritionDemandingUser& person):
    m_store{store},
    m_person{person}
{
}

void Analyzer::computeFoodPlan()
{
    GnuLinearSolver solver(GLP_MIN);
    
    const std::vector<Food>& allFood = m_store.getAllGoods();
    for (const Food& food : allFood)
    {
        solver.addProblemCoefficient(food.getCost());
        solver.addConstraintCoefficients(food.getNutritionValues());
        solver.addStructuralBound({GLP_DB, food.getMin(), food.getMax()});
    }

    const std::vector<double>& nutritionMinima = m_person.getNutritionMinima();
    for (double nutrition : nutritionMinima)
        solver.addAuxiliaryBound({GLP_LO, nutrition, 0.});

    solver.prepare();
    solver.solve();
    const std::vector<double>& results = solver.getResultVariables();
    
    for (unsigned i=0; i<results.size(); i++)
        m_foodAmount.push_back(results[i]);
        //     m_store.m_food[i].setAmount(results[i]);
}
