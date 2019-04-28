#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE analyzertest
#include <boost/test/unit_test.hpp>
#include "analyzer.hpp"
#include "solver.hpp"
#include "store.hpp"
#include "person.hpp"

BOOST_AUTO_TEST_SUITE( analyzertest )

// MOCK_BASE_CLASS( MockBound, Bound )
// {
//     MOCK_METHOD(getType, 0);
//     MOCK_METHOD(getLower, 0);
//     MOCK_METHOD(getUpper, 0);
// };

// MOCK_BASE_CLASS( MockSolver, Solver )
// {
//     MOCK_METHOD(getResultVariables, 0);
//     MOCK_METHOD(getResultValue, 0);
//     MOCK_METHOD(addProblemCoefficient, 1);
//     MOCK_METHOD(addConstraintCoefficients, 1);
//     MOCK_METHOD(addAuxiliaryBound, 1);
//     MOCK_METHOD(addStructuralBound, 1);
//     MOCK_METHOD(prepare, 0);
//     MOCK_METHOD(solve, 0);
// };

// MOCK_BASE_CLASS( MockStock, Stock )
// {
//     MOCK_METHOD(getName, 0);
//     MOCK_METHOD(getLocation, 0);
//     MOCK_METHOD(getAllGoods, 0, const std::vector<Food>&());
//     MOCK_METHOD(addGood, 1);
// };

// MOCK_BASE_CLASS( MockUser, User )
// {
//     MOCK_METHOD(setNutritionMinima, 1);
//     MOCK_METHOD(getNutritionMinima, 0);
// };

BOOST_AUTO_TEST_CASE( testConstructor )
{
    MockSolver* solver = new MockSolver;
    const MockStock* stock = new MockStock;
    const MockUser* user = new MockUser;

    Analyzer<MockGood> analyzer(stock, user, solver);
    // const std::vector<Good> food;
    // Analyzer analyzer(stock, user, solver);
    // MOCK_EXPECT( stock->getAllGoods ).once().with( food );
    // MOCK_EXPECT( solver->solve ).once();
    // analyzer.computeFoodPlan();
    // search: how to use mocking with vector (for store.test)
}

BOOST_AUTO_TEST_SUITE_END( )
