#include "store.hpp"
#include "person.hpp"
#include "solver.hpp"
#include "analyzer.hpp"
#include <json/json.h>
#include <memory>
#include <vector>
#include <string>

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

    m_solver->setAuxiliaryBound( m_person->getNutritionMinima(), {0});

    m_solver->prepare();
    m_solver->solve();

    m_store->decorateWithAmount( m_solver->getResultVariables() );

}

Json::Value Analyzer::toJson() const
{
    std::vector<double> totalNutritions = m_store->computeOptimizedTotalNutritions();
    Json::Value totalNutritionsOut;
    for (unsigned i=0; i<totalNutritions.size(); i++)
        totalNutritionsOut[std::to_string(i)] = totalNutritions[i];

    Json::Value out;
    out["food"] = m_store->toJson();
    out["optimizesTotalNutritions"] = totalNutritionsOut;

    return out;
}
