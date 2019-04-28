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
    auto solver = std::make_shared<MockSolver>();
    auto stock = std::make_shared<MockStock>();
    auto user = std::make_shared<MockUser>();
    
    stock->addGood({"PureNutrition1", {1, 0, 0}, 0, 100, .5});
    stock->addGood({"PureNutrition2", {0, 1, 0}, 0, 100, .2});

    Analyzer analyzer(stock, user, solver);
    analyzer.computeFoodPlan();

    std::vector<double> expectedAmount;
    for (const Food& food : stock->getAllGoods())
        expectedAmount.push_back(food.getCost());

    const std::vector<double>& actualAmount = analyzer.getAmounts();
    BOOST_TEST( expectedAmount == actualAmount, boost::test_tools::per_element() );
                
}

BOOST_AUTO_TEST_SUITE_END( )
