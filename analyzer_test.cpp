#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE analyzertest
#include <boost/test/unit_test.hpp>
#include <memory>
#include "analyzer.hpp"
#include "solver.hpp"
#include "store.hpp"
#include "person.hpp"

BOOST_AUTO_TEST_SUITE( analyzertest )

BOOST_AUTO_TEST_CASE( testCallToSolver_UserNutritionMinimaIsWrittenToSolverAmount )
{    
    auto store = std::make_unique<MockStore>();
    store->addGood({"PureNutrition1", {1, 0, 0}, .4, 100});
    store->addGood({"PureNutrition2", {0, 1, 0}, .5, 100});
    
    auto user = std::make_unique<MockUser>();
    std::vector<double> expectedAmount = {1., 2.};
    user->setNutritionMinima(expectedAmount);
    
    auto solver = std::make_unique<MockSolver>();

    Analyzer analyzer(std::move(store), std::move(user), std::move(solver));
    analyzer.computeFoodPlan();

    const std::vector<double>& actualAmount = analyzer.getAmounts();
    
    BOOST_TEST( expectedAmount == actualAmount );

    // std::ofstream fileOut("foodPlan.out");
    // fileOut << analyzer.toJson();
                
}

BOOST_AUTO_TEST_SUITE_END( )
