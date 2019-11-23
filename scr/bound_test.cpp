#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE boundtest

#include "bound.hpp"
#include <boost/test/unit_test.hpp>
#include <glpk.h>
#include <limits>

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
