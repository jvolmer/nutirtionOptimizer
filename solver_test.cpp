#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE solvertest
#include <boost/test/unit_test.hpp>
#include "solver.hpp"

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
        expectedValue = variableCoefficient[0] * expectedVariable[0] + variableCoefficient[1] * expectedVariable[1];

        BOOST_TEST( expectedVariable == *actualVariableAddress, boost::test_tools::per_element());
        BOOST_TEST( expectedValue == actualValue );
    }
};

BOOST_FIXTURE_TEST_SUITE( solvertest, fixture )

BOOST_AUTO_TEST_CASE( minimizationWithOneVariableAndNoAdditionalInequalityConstraints, * boost::unit_test::tolerance(1e-10))
{
    double xCoefficient = 2;
    std::vector<double> variableCoefficient{xCoefficient};
    double xLowerBound = 1;    
    std::vector<GnuLinearBound> constraintBound{{GLP_LO, xLowerBound, 0.}};

    std::vector<std::vector<double>> constraintCoefficient{{1}};
    std::vector<GnuLinearBound> variableBound{{GLP_LO, xLowerBound, 0}};

    GnuLinearSolver solver{GLP_MIN, variableCoefficient, std::move(constraintCoefficient), std::move(constraintBound), std::move(variableBound)};

    solve(solver);

    expectedVariable = {xLowerBound};

    verifyExpectedResults(std::move(variableCoefficient));
}

BOOST_AUTO_TEST_CASE( maximizationWithOneVariableAndNoAdditionalInequalityConstraints, * boost::unit_test::tolerance(1e-10))
{
    double xCoefficient = 2;
    std::vector<double> variableCoefficient{xCoefficient};
    double xUpperBound = 10;
    std::vector<GnuLinearBound> constraintBound{{GLP_UP, 0, xUpperBound}};

    std::vector<std::vector<double>> constraintCoefficient{{1}};
    std::vector<GnuLinearBound> variableBound{{GLP_UP, 0, xUpperBound}};

    GnuLinearSolver solver{GLP_MAX, variableCoefficient, std::move(constraintCoefficient), std::move(constraintBound), std::move(variableBound)};

    solve(solver);

    expectedVariable = {xUpperBound};

    verifyExpectedResults(std::move(variableCoefficient));
}

BOOST_AUTO_TEST_CASE( minimizationWithTwoVariablesAndOneAdditionalInequalityConstraint, * boost::unit_test::tolerance(1e-10))
{
    
    std::vector<double> variableCoefficient{1, 1};
    std::vector<std::vector<double>> constraintCoefficient{{1, 2}};
    std::vector<GnuLinearBound> constraintBound{{GLP_LO, 1, 0.}};
    std::vector<GnuLinearBound> variableBound{{GLP_LO, 0, 0}, {GLP_LO, 0, 0}};

    GnuLinearSolver solver{GLP_MIN, variableCoefficient, std::move(constraintCoefficient), std::move(constraintBound), std::move(variableBound)};

    solve(solver);

    expectedVariable = {0, .5};

    verifyExpectedResults(std::move(variableCoefficient));
}

BOOST_AUTO_TEST_CASE( maximizationWithTwoVariablesAndTwoAdditionalInequalityConstraint, * boost::unit_test::tolerance(1e-10))
{
    std::vector<double> variableCoefficient{.6, .5};
    std::vector<std::vector<double>> constraintCoefficient{{1, 2}, {3, 1}};
    std::vector<GnuLinearBound> constraintBound{{GLP_UP, 0, 1}, {GLP_UP, 0, 2}};
    std::vector<GnuLinearBound> variableBound{{GLP_LO, 0, 0}, {GLP_LO, 0, 0}};

    GnuLinearSolver solver{GLP_MAX, variableCoefficient, std::move(constraintCoefficient), std::move(constraintBound), std::move(variableBound)};

    solve(solver);

    expectedVariable = {.6, .2};

    verifyExpectedResults(std::move(variableCoefficient));

}

BOOST_AUTO_TEST_SUITE_END( )
