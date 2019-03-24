#include "store.hpp"

Store::Store(const std::string& name, const std::string& fileName):
    m_name {name},
    m_fileName {fileName}
{
}

void Store::computeFoodPlan(const Person& person)
{
    GnuLinearSolver solver(GLP_MIN);
    
    for (const Food& food : m_food)
    {
        solver.addProblemCoefficient(food.getCost());
        solver.addConstraintCoefficients(food.getNutritionValues());
        solver.addStructuralBound({GLP_DB, food.getMin(), food.getMax()});
    }

    const std::vector<double>& nutritionMinima = person.getNutritionMinima();
    for (double nutrition : nutritionMinima)
        solver.addAuxiliaryBound({GLP_LO, nutrition, 0.});

    solver.prepare();
    solver.solve();
    const std::vector<double>& results = solver.getResultVariables();
    
    for (unsigned i=0; i<m_food.size(); i++)
        m_food[i].setAmount(results[i]);
}
