#include "food.hpp"
#include "store.hpp"
#include "person.hpp"
#include "solver.hpp"
#include "analyzer.hpp"

int main(){

    // fill store
    auto store = std::make_unique<FoodStore>("Kueche");
    store->addGood({"Spitzkohl", {0.02, 0.26, 0}, 0, 300});
    store->addGood({"Wirsing", {0.03, 0.34, 0}, 0, 300});
    store->addGood({"Rote Beete", {0.02, 0.00001, 0}, 0, 100});
    store->addGood({"Walnuesse", {.14, .10, 0}, 0, 50});
    store->addGood({"Makrelenfilet", {.19, 0.04549, 0.00792}, 0, 500});
    store->addGood({"Avokado", {.01, .08112, 0}, 0, 20});
    store->addGood({"Leinoel", {0, .18168, 0}, 0, 5});

    // choose preference of foods (low number means a larger preference)
    store->decorateWithCost({.5, .5, .001, 1, .001, .5, .5});

    // create user with minimal nutrition needs per day
    auto user = std::make_unique<NutritionDemandingUser>("Julia");
    user->setNutritionMinima({80, 45, 3});

    // create solver
    auto solver = std::make_unique<GnuLinearSolver>(GLP_MIN);

    // create analyzer and optimize food
    Analyzer analyzer(std::move(store), std::move(user), std::move(solver));
    analyzer.computeFoodPlan();
    std::cout << analyzer.toJson() << std::endl;
}
