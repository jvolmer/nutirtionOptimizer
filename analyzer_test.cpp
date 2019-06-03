#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE analyzertest
#include <boost/test/unit_test.hpp>
#include <memory>
#include "analyzer.hpp"
#include "solver.hpp"
#include "store.hpp"
#include "person.hpp"

BOOST_AUTO_TEST_SUITE( analyzertest )

BOOST_AUTO_TEST_CASE( testCallToSolver )
{    
    auto store = std::make_shared<MockStore>();
    store->addGood({"PureNutrition1", {1, 0, 0}, 0, 100, .5});
    store->addGood({"PureNutrition2", {0, 1, 0}, 0, 100, .2});

    auto user = std::make_shared<MockUser>();
    auto solver = std::make_shared<MockSolver>();

    Analyzer analyzer(store, user, solver);
    analyzer.computeFoodPlan();

    std::vector<double> expectedAmount;
    for (const Food& food : store->getAllGoods())
        expectedAmount.push_back(food.getCost());

    std::vector<double> actualAmount;
    for (const Analyzed& ana : analyzer.getFoodPlan())
        actualAmount.push_back(ana.getAmount());
    
    // const std::vector<double>& actualAmount = analyzer.getAmounts();
    BOOST_TEST( expectedAmount == actualAmount, boost::test_tools::per_element() );

    // std::ofstream fileOut("foodPlan.out");
    // fileOut << analyzer.toJson();
                
}

BOOST_AUTO_TEST_SUITE_END( )
