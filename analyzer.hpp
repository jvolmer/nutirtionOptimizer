#ifndef ANALYZER_H
#define ANALYZER_H
#include <memory>
#include "store.hpp"
#include "person.hpp"
#include "solver.hpp"
#include "food.hpp"

class Analyzer{

private:
    std::unique_ptr<Store> m_store;
    std::unique_ptr<User> m_person;
    std::unique_ptr<Solver> m_solver;
    
public:
    Analyzer(std::unique_ptr<Store> store, std::unique_ptr<User> person, std::unique_ptr<Solver> solver);
    Analyzer(std::unique_ptr<Store> store) {};
    Analyzer() {};
    ~Analyzer() {};

    const std::vector<double>& getAmounts() const { return m_solver->getResultVariables(); }
    void computeFoodPlan();

    Json::Value toJson() const;
};


#endif
