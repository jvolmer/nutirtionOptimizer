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

BOOST_AUTO_TEST_CASE( computeFoodPlan )
{
    Store store("Kueche");
    store.addGood({"Eiweiss", {1, 0, 0}, 0, 1000});
    store.addGood({"MUFA", {0, 1, 0}, 0, 1000});
    store.addGood({"Eicosapentaensaeure", {0, 0, 1}, 0, 1000});
 
    NutritionDemandingUser julia("Julia");
    julia.setNutritionMinima({1, 1, 1});

    Analyzer analyzer(store, julia);
    analyzer.computeFoodPlan();

    std::vector<double> expectedValue{1, 1, 1};

    const std::vector<double>& foodAmount = analyzer.getAmounts();
    for (unsigned i=0;i < foodAmount.size(); i++)
        BOOST_TEST( foodAmount[i] == expectedValue[i] );
}


BOOST_AUTO_TEST_SUITE_END( )
