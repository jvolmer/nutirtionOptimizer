#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE foodtest
#include <boost/test/unit_test.hpp>
#include <string>
#include "food.hpp"

BOOST_AUTO_TEST_SUITE (foodtest)

BOOST_AUTO_TEST_CASE( initializeWithName )
{
    std::string testName{"banane"};
    Food testFood{testName};
    
    BOOST_CHECK_EQUAL( testFood.getName(), testName );
    BOOST_CHECK_CLOSE_FRACTION( testFood.getMin(), 0., 1e-10);
    BOOST_CHECK_CLOSE_FRACTION( testFood.getMax(), 0., 1e-10);
}

BOOST_AUTO_TEST_CASE( initializeWithMinMax )
{
    std::string testName{"apfel"};
    double testMin{5.};
    double testMax{10.};
    Food testFood{testName, testMin, testMax};
    
    BOOST_CHECK_EQUAL( testFood.getName(), testName );
    BOOST_CHECK_CLOSE_FRACTION( testFood.getMin(), testMin, 1e-10 );
    BOOST_CHECK_CLOSE_FRACTION( testFood.getMax(), testMax, 1e-10 );
}

BOOST_AUTO_TEST_CASE( initializeWithNutritionValues )
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

BOOST_AUTO_TEST_CASE( compareTwoFoods )
{
    std::vector<double> nutrition {1.2, 100, 204};
    Food testFood1{"himbeere", nutrition, 3, 2};
    Food testFood2{"himbeere", nutrition, 3, 2};
    BOOST_CHECK( testFood1 == testFood2 );
}

// BOOST_AUTO_TEST_CASE( initializeWithString )
// {
//     std::string name{"apfel"};
//     double min{1};
//     double max{3};
//     std::vector<double> nutrition{100, 20, 1.3};
//     Food testFood{name, nutrition, min, max};
//     std::string foodString{name + "\t" + to_string(min) + "\t" + to_string(max) + "\t" + to_string(nutrition) + "\n"};
//         // {"apfel\t1\t3\t100\t20\t1.3\n"};

// }

BOOST_AUTO_TEST_SUITE_END( )
