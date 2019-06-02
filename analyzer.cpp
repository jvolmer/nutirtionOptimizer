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

    m_solver->prepare();
    m_solver->solve();
    const std::vector<double>& results = m_solver->getResultVariables();

    for (unsigned i=0; i<results.size(); i++)
        m_goodAmount.push_back(results[i]);
        //     m_store.m_food[i].setAmount(results[i]);
}

Json::Value Analyzer::toJson() const
{
    Json::Value foodAmounts;
    const std::vector<Food>& allFood = m_store->getAllGoods();
    std::vector<double> totalNutritions = {0};
    totalNutritions.resize(m_store->getNumberOfNutritions(), 0);
    for (unsigned ifood=0; ifood<allFood.size(); ifood++)
    {
        Json::Value oneFood;
        oneFood = allFood[ifood].toJson();
        // oneFood["name"] = food.getName();
        oneFood["amount"] = m_goodAmount[ifood];
        foodAmounts.append(oneFood);

        const std::vector<double>& nutritions = allFood[ifood].getNutritionValues();
        for (unsigned inutr=0; inutr<nutritions.size(); inutr++)
            totalNutritions[inutr] += nutritions[inutr] * m_goodAmount[ifood];
    }

    Json::Value totalNutritionsOut;
    for (unsigned i=0; i<totalNutritions.size(); i++)
        totalNutritionsOut[std::to_string(i)] = totalNutritions[i];

    Json::Value out;
    out["food"] = foodAmounts;
    out["totalNutritions"] = totalNutritionsOut;

    return out;
}
