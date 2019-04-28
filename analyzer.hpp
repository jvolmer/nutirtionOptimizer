#ifndef ANALYZER_H
#define ANALYZER_H
#include "store.hpp"
#include "person.hpp"
#include "solver.hpp"
#include "food.hpp"

template <class T>
class Analyzer{

private:
    const Stock<T>* m_store;
    const User* m_person;
    Solver* m_solver;
    std::vector<double> m_goodAmount;

public:
    Analyzer(const Stock<T>* store, const User* person, Solver* solver);
    // Analyzer(const Stock<T>* store, const User* person);
    Analyzer(const Stock<T>* store) {};
    Analyzer(const User* person);
    Analyzer() {};
    ~Analyzer() {};

    const std::vector<double>& getAmounts() const { return m_goodAmount; } 
    void computeFoodPlan();
};


#endif


template <class T>
Analyzer<T>::Analyzer(const Stock<T>* store, const User* person, Solver* solver):
    m_store{store},
    m_person{person},
    m_solver{solver}
{
}

