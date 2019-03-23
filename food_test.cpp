#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE foodtest
#include <boost/test/unit_test.hpp>
#include <string>
#include "food.hpp"

BOOST_AUTO_TEST_SUITE (foodtest)

BOOST_AUTO_TEST_CASE( initializeFoodWithName )
{
    std::string testName{"banane"};
    Food testFood{testName};
    
    BOOST_CHECK_EQUAL( testFood.getName(), testName );
    BOOST_CHECK_CLOSE_FRACTION( testFood.getMin(), 0., 1e-10);
    BOOST_CHECK_CLOSE_FRACTION( testFood.getMax(), 0., 1e-10);
}

BOOST_AUTO_TEST_CASE( initializeFoodWithMinMax )
{
    std::string testName{"apfel"};
    double testMin{5.};
    double testMax{10.};
    Food testFood{testName, testMin, testMax};
    
    BOOST_CHECK_EQUAL( testFood.getName(), testName );
    BOOST_CHECK_CLOSE_FRACTION( testFood.getMin(), testMin, 1e-10 );
    BOOST_CHECK_CLOSE_FRACTION( testFood.getMax(), testMax, 1e-10 );
}

BOOST_AUTO_TEST_CASE( initializeFoodWithNutritionValues )
{
    std::string testName{"spitzkohl"};
    std::vector<double> nutrition {1.2, 100, 204};
    Food testFood{testName, nutrition};

    BOOST_CHECK_EQUAL( testFood.getName(), testName );
    BOOST_CHECK( testFood.getNutritionValues() == nutrition );
}

BOOST_AUTO_TEST_CASE( checkMinMaxHierarchy )
{
    double minIn{100.};
    double maxIn{50.};
    Food testFood{"erdbeere", minIn, maxIn};

    BOOST_CHECK_EQUAL( testFood.getMax(), minIn );
    BOOST_CHECK_EQUAL( testFood.getMin(), maxIn );
}

BOOST_AUTO_TEST_SUITE_END( )
