#include "food.hpp"
#include "store.hpp"
#include "person.hpp"
#include "solver.hpp"
#include "analyzer.hpp"
#include <iostream>

int main(){

    auto store = std::make_unique<FoodStore>("Kueche");
    
    // nutritions: Omega3 (EPA+DHA), VitaminD, VitaminC
    store->addGood({"Makrelenfilet gekocht", {0.02462, 0.000000168, 0.000014}, 0, 500});
    store->addGood({"Lachs angebraten", {0.00439, 0.000000094, 0}, 0, 500});
    store->addGood({"Gruenkohl gekocht", {0, 0.000000001, 0.000393}, 0, 1000});
    store->addGood({"Wirsing gekocht", {0, 0, 0.000257}, 0, 1000});
    
    store->decorateWithCost({1, .001, .5, 1});

    auto user = std::make_unique<NutritionDemandingUser>("Peter");
    user->setNutritionMinima({1, 0.00002, .05});
    user->setNutritionMaxima({2, 0.00005, .15});
    
    auto solver = std::make_unique<GnuLinearSolver>(GLP_MIN);

    Analyzer analyzer(std::move(store), std::move(user), std::move(solver));
    analyzer.computeFoodPlan();
    std::cout << analyzer.toJson() << std::endl;
}
