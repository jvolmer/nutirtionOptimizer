#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE integrationtest_analyzer
#include <boost/test/unit_test.hpp>
#include "analyzer.hpp"
#include "store.hpp"
#include "food.hpp"
#include "store.hpp"

BOOST_AUTO_TEST_SUITE( integrationtest_analyzer )

BOOST_AUTO_TEST_CASE( test )
{
}

BOOST_AUTO_TEST_CASE( nutritionsAreSeperateFoods )
{
    auto store = std::make_unique<FoodStore>("Kueche");
    store->addGood({"Eiweiss", {1, 0, 0}, 0, 1000});
    store->addGood({"MUFA", {0, 1, 0}, 0, 1000});
    store->addGood({"Eicosapentaensaeure", {0, 0, 1}, 0, 1000});
    std::vector<double> costs{.4, .3, .5};
    store->decorateWithCost(std::move(costs));
    
    auto user = std::make_unique<NutritionDemandingUser>("Julia");
    user->setNutritionMinima({1, 1, 1});

    auto solver = std::make_unique<GnuLinearSolver>(GLP_MIN);
    
    Analyzer analyzer(std::move(store), std::move(user), std::move(solver));
    analyzer.computeFoodPlan();

    const std::vector<double> expectedAmount{1, 1, 1};
    const std::vector<double>& actualAmount = analyzer.getAmounts();
    
    BOOST_TEST( expectedAmount[1] == actualAmount[1] );
}


BOOST_AUTO_TEST_SUITE_END( )
