#ifndef ANALYZER_H
#define ANALYZER_H
#include <memory>
#include "store.hpp"
#include "person.hpp"
#include "solver.hpp"
#include "food.hpp"

class Analyzer{

private:
    std::shared_ptr<Stock> m_store;
    std::shared_ptr<User> m_person;
    std::shared_ptr<Solver> m_solver;
    std::vector<double> m_goodAmount;

public:
    Analyzer(std::shared_ptr<Stock> store, std::shared_ptr<User> person, std::shared_ptr<Solver> solver);
    Analyzer(std::shared_ptr<Stock> store) {};
    Analyzer() {};
    ~Analyzer() {};

    const std::vector<double>& getAmounts() const { return m_goodAmount; } 
    void computeFoodPlan();
};


#endif
