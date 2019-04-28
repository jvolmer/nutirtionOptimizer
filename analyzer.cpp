#include "analyzer.hpp"

Analyzer::Analyzer(std::shared_ptr<Store> store, std::shared_ptr<User> person, std::shared_ptr<Solver> solver):
    m_store{store},
    m_person{person},
    m_solver{solver}
{
}

void Analyzer::computeFoodPlan()
{
    const std::vector<Food>& allFood = m_store->getAllGoods();
    for (const Food& food : allFood)
    {
        m_solver->addProblemCoefficient(food.getCost());
        m_solver->addConstraintCoefficients(food.getNutritionValues());
        m_solver->addStructuralBound({GLP_DB, food.getMin(), food.getMax()});
    }

    const std::vector<double>& nutritionMinima = m_person->getNutritionMinima();
    for (double nutrition : nutritionMinima)
        m_solver->addAuxiliaryBound({GLP_LO, nutrition, 0.});

    m_solver->prepareStructuralVariables();
    m_solver->prepareAuxiliaryVariables();
    m_solver->solve();
    const std::vector<double>& results = m_solver->getResultVariables();

    for (unsigned i=0; i<results.size(); i++)
        m_goodAmount.push_back(results[i]);
        //     m_store.m_food[i].setAmount(results[i]);
}
