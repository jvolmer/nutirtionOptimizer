#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE foodtest
#include <boost/test/unit_test.hpp>
#include <string>
#include "food.hpp"

BOOST_AUTO_TEST_SUITE (foodtest)

BOOST_AUTO_TEST_CASE( initializeFoodWithName )
{
    std::string testValue{"banane"};
    Food noFood{testValue};
    
    BOOST_CHECK_EQUAL( noFood.getName(), testValue );
    BOOST_CHECK_EQUAL( noFood.getFamily(), "" );
    BOOST_CHECK_CLOSE_FRACTION( noFood.getCarbonhydrateValue(), 0., 1e-10);
}

BOOST_AUTO_TEST_CASE( initializeFoodWithNameAndNutritionValue )
{
    std::string testName{"apfel"};
    double testNutrition{5.};
    Food noFood{testName, testNutrition};
    
    BOOST_CHECK_EQUAL( noFood.getName(), testName );
    BOOST_CHECK_CLOSE_FRACTION( noFood.getCarbonhydrateValue(), testNutrition, 1e-10 );
}

BOOST_AUTO_TEST_SUITE_END( )
