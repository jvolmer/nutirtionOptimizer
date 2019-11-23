#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE integrationtest_analyzer

#include "food.hpp"
#include "store.hpp"
#include "store.hpp"
#include "solver.hpp"
#include "analyzer.hpp"
#include <boost/test/unit_test.hpp>
#include <memory>
#include <vector>
#include <fstream>
#include <iostream>

BOOST_AUTO_TEST_SUITE( integrationtest_analyzer )

BOOST_AUTO_TEST_CASE( nutritionsAreSeperateFoods )
{
    auto store = std::make_unique<FoodStore>("Kueche");
    store->addGood({"Eiweiss", {1, 0, 0}, 0, 1000});
    store->addGood({"MUFA", {0, 1, 0}, 0, 1000});
    store->addGood({"Eicosapentaensaeure", {0, 0, 1}, 0, 1000});
    std::vector<double> costs{.4, .3, .5};
    store->decorateWithCost(std::move(costs));
    
    auto user = std::make_unique<NutritionDemandingUser>("Julia");
    const std::vector<double> nutritionMinima {1, 2, 1};
    user->setNutritionMinima(nutritionMinima);
    const std::vector<double> nutritionMaxima {10, 20, 50};
    user->setNutritionMaxima(nutritionMaxima);

    auto solver = std::make_unique<GnuLinearSolver>(GLP_MIN);
    
    Analyzer analyzer(std::move(store), std::move(user), std::move(solver));
    analyzer.computeFoodPlan();

    const std::vector<double> expectedAmount = nutritionMinima;
    const std::vector<double>& actualAmount = analyzer.getAmounts();
    
    BOOST_TEST( expectedAmount[1] == actualAmount[1] );

    std::ofstream fileOut("analyzer.out");
    fileOut << analyzer.toJson();
    std::cout << "> Wrote Analyzer to analyzer.out" << std::endl;
}

BOOST_AUTO_TEST_SUITE_END( )
