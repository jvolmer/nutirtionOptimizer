#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE solvertest

#include "solver.hpp"
#include <boost/test/unit_test.hpp>
#include <cmath>
#include <vector>
#include <utility>
#include <limits>
#include <iostream>


struct fixture
{
    std::vector<double> expectedVariable;
    double expectedValue;
    const std::vector<double>* actualVariableAddress;
    double actualValue;

    void solve(GnuLinearSolver& solver)
    {
        solver.prepare();
        solver.solve();
        actualVariableAddress = &(solver.getResultVariables());
        actualValue = solver.getResultValue();
    }
    
    void verifyExpectedResults(const std::vector<double>& variableCoefficient)
    {
        expectedValue = 0;
        for (unsigned i=0; i<variableCoefficient.size(); i++)
            expectedValue += variableCoefficient[i] * expectedVariable[i];
        
        BOOST_TEST( expectedVariable == *actualVariableAddress, boost::test_tools::per_element());
        BOOST_TEST( expectedValue == actualValue );
    }
};


BOOST_AUTO_TEST_SUITE( bound )

BOOST_AUTO_TEST_CASE( doubleBoundInitialization, * boost::unit_test::tolerance(1e-10))
{
    double lowerBound = 1;
    double upperBound = 2;
    GnuLinearBound bound{lowerBound, upperBound};
    BOOST_TEST( bound.getLower() == lowerBound );
    BOOST_TEST( bound.getUpper() == upperBound );
    BOOST_TEST( bound.getType() == GLP_DB );
}

BOOST_AUTO_TEST_CASE( lowerBoundInitialization, * boost::unit_test::tolerance(1e-10))
{
    double lowerBound = 1;
    double upperBound = std::numeric_limits<double>::infinity();
    GnuLinearBound bound{lowerBound, upperBound};
    BOOST_TEST( bound.getLower() == lowerBound );
    BOOST_TEST( bound.getUpper() == 0 );
    BOOST_TEST( bound.getType() == GLP_LO );
}

BOOST_AUTO_TEST_CASE( upperBoundInitialization, * boost::unit_test::tolerance(1e-10))
{
    double lowerBound = std::numeric_limits<double>::infinity();
    double upperBound = 10;
    GnuLinearBound bound{lowerBound, upperBound};
    BOOST_TEST( bound.getLower() == 0 );
    BOOST_TEST( bound.getUpper() == upperBound );
    BOOST_TEST( bound.getType() == GLP_UP );
}

BOOST_AUTO_TEST_SUITE_END( )


BOOST_FIXTURE_TEST_SUITE( solvertest, fixture )

BOOST_AUTO_TEST_CASE( minimizationWithOneVariable_NoAdditionalInequalityConstraints, * boost::unit_test::tolerance(1e-10))
{
    double infinity = std::numeric_limits<double>::infinity();
    std::vector<double> problemCoefficient{2};
    double xLowerBound = 1;

    GnuLinearSolver solver{GLP_MIN};
    solver.setProblemCoefficient(problemCoefficient);
    solver.setConstraintCoefficients({{1}});
    solver.setStructuralBound({xLowerBound}, {infinity});
    solver.setAuxiliaryBound({xLowerBound}, {infinity});
    
    solve(solver);

    expectedVariable = {xLowerBound};

    verifyExpectedResults(std::move(problemCoefficient));
}

BOOST_AUTO_TEST_CASE( maximizationWithOneVariable_NoAdditionalInequalityConstraints, * boost::unit_test::tolerance(1e-10))
{
    double infinity = std::numeric_limits<double>::infinity();
    std::vector<double> problemCoefficient{2};
    double xUpperBound = 10;

    GnuLinearSolver solver{GLP_MAX};
    solver.setProblemCoefficient(problemCoefficient);
    solver.setConstraintCoefficients({{1}});
    solver.setStructuralBound({infinity}, {xUpperBound});
    solver.setAuxiliaryBound({infinity}, {xUpperBound});
    
    solve(solver);

    expectedVariable = {xUpperBound};

    verifyExpectedResults(std::move(problemCoefficient));
}

BOOST_AUTO_TEST_CASE( minimizationWithTwoVariables_OneAdditionalInequalityConstraint, * boost::unit_test::tolerance(1e-10))
{

    double infinity = std::numeric_limits<double>::infinity();
    std::vector<double> problemCoefficient{1, 1};
    
    GnuLinearSolver solver{GLP_MIN};
    solver.setProblemCoefficient(problemCoefficient);
    solver.setConstraintCoefficients({{1, 2}});
    solver.setStructuralBound({0, 0}, {infinity, infinity});
    solver.setAuxiliaryBound({1}, {infinity});

    solve(solver);

    expectedVariable = {0, .5};

    verifyExpectedResults(std::move(problemCoefficient));
}

BOOST_AUTO_TEST_CASE( maximizationWithTwoVariables_TwoAdditionalInequalityConstraint, * boost::unit_test::tolerance(1e-10))
{
    double infinity = std::numeric_limits<double>::infinity();
    std::vector<double> problemCoefficient{.6, .5};

    GnuLinearSolver solver{GLP_MAX};
    solver.setProblemCoefficient(problemCoefficient);
    solver.setConstraintCoefficients({{1, 2}, {3, 1}});
    solver.setStructuralBound({0, 0}, {infinity, infinity});
    solver.setAuxiliaryBound({infinity, infinity}, {1, 2});

    solve(solver);

    expectedVariable = {.6, .2};

    verifyExpectedResults(std::move(problemCoefficient));

}

BOOST_AUTO_TEST_SUITE_END( )
