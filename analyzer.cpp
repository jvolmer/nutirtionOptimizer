#include "analyzer.hpp"

Analyzer::Analyzer(std::unique_ptr<Store> store, std::unique_ptr<User> person, std::unique_ptr<Solver> solver):
    m_store{std::move(store)},
    m_person{std::move(person)},
    m_solver{std::move(solver)}
{
}

void Analyzer::computeFoodPlan()
{
    m_solver->setProblemCoefficient( m_store->getFoodPropertyVector("cost") );
    m_solver->setConstraintCoefficients( m_store->getFoodNutritionValues() );

    m_solver->setStructuralBound(
        m_store->getFoodPropertyVector("min"),
        m_store->getFoodPropertyVector("max")
        );
    // for (unsigned i=0; i<cost.size(); i++)
    // {
    //     m_solver->addProblemCoefficient(cost[i]);
    //     m_solver->addConstraintCoefficients(nutrition[i]);
    //     m_solver->addStructuralBound({GLP_DB, min[i], max[i]});
    // }

    m_solver->setAuxiliaryBound( m_person->getNutritionMinima(), {0});

    // for (double nutrition : nutritionMinima)
    //     m_solver->addAuxiliaryBound({GLP_LO, nutrition, 0.});

    m_solver->prepare();
    m_solver->solve();

    // const std::vector<double>& results = m_solver->getResultVariables();
    m_store->decorateWithAmount( m_solver->getResultVariables() );

    // for (unsigned i=0; i<results.size(); i++)
    // {
    //     // m_analyzedGoods.push_back(Analyzed(&allFood[i], results[i]));
    //     m_goodAmount.push_back(results[i]);
    //     // m_store.m_food[i].setAmount(results[i]);
    // }
}

// Json::Value Analyzer::toJson() const
// {
//     Json::Value foodAmounts;
//     const std::vector<Food>& allFood = m_store->getAllGoods();
//     std::vector<double> totalNutritions = {0};
//     totalNutritions.resize(m_store->getNumberOfNutritions(), 0);
//     for (unsigned ifood=0; ifood<allFood.size(); ifood++)
//     {
//         Json::Value oneFood;
//         oneFood = allFood[ifood].toJson();
//         // oneFood["name"] = food.getName();
//         oneFood["amount"] = m_goodAmount[ifood];
//         foodAmounts.append(oneFood);

//         const std::vector<double>& nutritions = allFood[ifood].getNutritionValues();
//         for (unsigned inutr=0; inutr<nutritions.size(); inutr++)
//             totalNutritions[inutr] += nutritions[inutr] * m_goodAmount[ifood];
//     }

//     Json::Value totalNutritionsOut;
//     for (unsigned i=0; i<totalNutritions.size(); i++)
//         totalNutritionsOut[std::to_string(i)] = totalNutritions[i];

//     Json::Value out;
//     out["food"] = foodAmounts;
//     out["totalNutritions"] = totalNutritionsOut;

//     return out;
// }
