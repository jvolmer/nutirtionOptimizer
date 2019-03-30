#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE foodtest
#include <boost/test/unit_test.hpp>
#include <string>
#include "food.hpp"

BOOST_AUTO_TEST_SUITE (initialize_food)

BOOST_AUTO_TEST_CASE( initializeWithName )
{
    std::string testName{"banane"};
    Food testFood{testName};
    
    BOOST_TEST( testFood.getName() == testName );
    BOOST_TEST( testFood.getMin() == 0.);
    BOOST_TEST( testFood.getMax() == 0.);
}

BOOST_AUTO_TEST_CASE( initializeWithMinMax )
{
    std::string testName{"apfel"};
    double testMin{5.};
    double testMax{10.};
    Food testFood{testName, testMin, testMax};
    
    BOOST_TEST( testFood.getName() == testName );
    BOOST_TEST( testFood.getMin() == testMin );
    BOOST_TEST( testFood.getMax() == testMax );
}

BOOST_AUTO_TEST_CASE( initializeWithNutritionValues )
{
    std::string testName{"spitzkohl"};
    std::vector<double> nutrition {1.2, 100, 204};
    Food testFood{testName, nutrition};

    BOOST_TEST( testFood.getName() == testName );
    BOOST_TEST( testFood.getNutritionValues() == nutrition );
}

BOOST_AUTO_TEST_CASE( checkMinMaxHierarchy )
{
    double minIn{100.};
    double maxIn{50.};
    Food testFood{"erdbeere", minIn, maxIn};

    BOOST_TEST( testFood.getMax() == minIn );
    BOOST_TEST( testFood.getMin() == maxIn );
}

BOOST_AUTO_TEST_SUITE_END( );


BOOST_AUTO_TEST_SUITE( compare_food )
    
BOOST_AUTO_TEST_CASE( compareEqualFoods )
{
    std::vector<double> nutrition {1.2, 100, 204};
    Food testFood1{"himbeere", nutrition, 3, 2};
    Food testFood2{"himbeere", nutrition, 3, 2};
    BOOST_TEST( testFood1 == testFood2 );
}

BOOST_AUTO_TEST_CASE( compareFoodsWithDifferentNames )
{
    std::vector<double> nutrition {1.2, 100, 204};
    std::string test="erdbeere";
    std::string test2="himbeere";
    Food testFood1{test, nutrition, 3, 2};
    Food testFood2{test2, nutrition, 3, 2};
    BOOST_TEST( !(testFood1 == testFood2) );
}

BOOST_AUTO_TEST_CASE( compareFoodsWithDifferentNutritions )
{
    std::vector<double> nutrition1 {1.2, 100, 204};
    std::vector<double> nutrition2 {1.3, 100, 204};
    Food testFood1{"himbeere", nutrition1, 3, 2};
    Food testFood2{"himbeere", nutrition2, 3, 2};
    BOOST_TEST( !(testFood1 == testFood2) );
}

BOOST_AUTO_TEST_SUITE_END( )
