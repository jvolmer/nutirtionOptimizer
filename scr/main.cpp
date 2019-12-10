#include "food.hpp"
#include "store.hpp"
#include "person.hpp"
#include "solver.hpp"
#include "analyzer.hpp"
#include <iostream>

int main(){

    // fill store
    auto store = std::make_unique<FoodStore>("Kueche");
    store->addGood({"Spitzkohl", {0.02, 0.26, 0}, 0, 1000});
    store->addGood({"Wirsing", {0.03, 0.34, 0}, 0, 1000});
    store->addGood({"Rote Beete", {0.02, 0.00001, 0}, 0, 1000});
    store->addGood({"Walnuesse", {.14, .10, 0}, 0, 100});
    store->addGood({"Makrelenfilet", {.19, 0.04549, 0.00792}, 0, 500});
    store->addGood({"Avokado", {.01, .08112, 0}, 0, 100});
    store->addGood({"Leinoel", {0, .18168, 0}, 0, 10});

    // choose preference of foods (low number means a larger
    // preference)
    const std::vector<double> cost {.5, .5, .001, 1, .001, .5, .5};
    store->decorateWithCost(cost);

    // create user with minimal nutrition needs per day
    auto user = std::make_unique<NutritionDemandingUser>("Peter");
    const std::vector<double> minima {2, 2, .1};
    user->setNutritionMinima(minima);
    const std::vector<double> maxima {100, 100, 100};
    user->setNutritionMaxima(maxima);
    
    // create solver
    auto solver = std::make_unique<GnuLinearSolver>(GLP_MIN);

    // create analyzer and optimize food
    Analyzer analyzer(std::move(store), std::move(user), std::move(solver));
    analyzer.computeFoodPlan();
    std::cout << analyzer.toJson() << std::endl;
}
