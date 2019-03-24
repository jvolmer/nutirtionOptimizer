#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE solvertest
#include <boost/test/unit_test.hpp>
#include "solver.hpp"

BOOST_AUTO_TEST_SUITE( solvertest )

BOOST_AUTO_TEST_CASE( solveSystem, * boost::unit_test::tolerance(1e-10))
{
    GnuLinearSolver solver(GLP_MAX);

    solver.addProblemCoefficient(0.6);
    solver.addProblemCoefficient(0.5);
    solver.addConstraintCoefficients({1., 3.});
    solver.addConstraintCoefficients({2., 1.});
    
    solver.addAuxiliaryBound({GLP_UP, 0., 1.});
    solver.addAuxiliaryBound({GLP_UP, 0., 2.});
    solver.addStructuralBound({GLP_LO, 0., 0.});
    solver.addStructuralBound({GLP_LO, 0., 0.});

    solver.prepare();
    solver.solve();
    double solverValue =solver.getResultValue();
    const std::vector<double>& solverVariable = solver.getResultVariables();
    
    double expectedValue{0.46};
    std::vector<double> expectedVariable{0.6, 0.2};

    BOOST_TEST( expectedVariable == solverVariable, boost::test_tools::per_element());
    BOOST_TEST( expectedValue == solverValue );
}

BOOST_AUTO_TEST_SUITE_END( )
