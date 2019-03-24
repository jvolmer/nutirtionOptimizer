#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE solvertest
#include <boost/test/unit_test.hpp>
#include "solver.hpp"

BOOST_AUTO_TEST_SUITE( solvertest )

BOOST_AUTO_TEST_CASE( initialize, * boost::unit_test::tolerance(1e-10))
{
    GnuLinearSolver solver("testSolver", GLP_MAX);

    solver.addProblemCoefficient(0.6);
    solver.addProblemCoefficient(0.5);
    std::vector<double> ccoeff1{1., 2.};
    std::vector<double> ccoeff2{3., 1.};
    solver.addConstraintCoefficients(ccoeff1);
    solver.addConstraintCoefficients(ccoeff2);
    
    GnuLinearBound auxiliary1 {GLP_UP, 0., 1.};
    GnuLinearBound auxiliary2 {GLP_UP, 0., 2.};
    GnuLinearBound structural1 {GLP_LO, 0., 0.}; 
    GnuLinearBound structural2 {GLP_LO, 0., 0.};
    solver.addAuxiliaryBound(auxiliary1);
    solver.addAuxiliaryBound(auxiliary2);
    solver.addStructuralBound(structural1);
    solver.addStructuralBound(structural2);

    solver.prepare();
    solver.solve();
    const std::vector<double>& solverResult = solver.getResultVariables();
    double solverValue =solver.getResultProblemValue();
    
    std::vector<double> expectedVariable{0.6, 0.2};
    double expectedValue{0.46};
    BOOST_TEST( expectedVariable == solverResult, boost::test_tools::per_element());
    // BOOST_CHECK_EQUAL_COLLECTIONS(expectedVariable.begin(), expectedVariable.end(), solverResult.begin(), solverResult.end());
    // BOOST_CHECK_CLOSE_FRACTION( expectedVariable, solverResult, 1e-10, boost::test_tools::per_element);
    // BOOST_CHECK_CLOSE_FRACTION( expectedValue, solverValue, 1e-10);
    BOOST_TEST( expectedValue == solverValue );
}

BOOST_AUTO_TEST_SUITE_END( )
