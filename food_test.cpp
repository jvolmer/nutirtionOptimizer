#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE foodtest
#include <boost/test/unit_test.hpp>
#include <string>
#include <json/json.h>
#include "food.hpp"

BOOST_AUTO_TEST_SUITE (initialize_food)

BOOST_AUTO_TEST_CASE( initializeWithoutInput )
{
    Food testFood;
    BOOST_TEST( testFood.getName() == "");
}

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
    Food testFood{testName, {}, testMin, testMax};
    
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
    Food testFood{"erdbeere", {}, minIn, maxIn};

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
    Food testFood1{"himbeere", std::move(nutrition1), 3, 2};
    Food testFood2{"himbeere", std::move(nutrition2), 3, 2};
    BOOST_TEST( !(testFood1 == testFood2) );
}

BOOST_AUTO_TEST_SUITE_END( )


BOOST_AUTO_TEST_SUITE( json )

BOOST_AUTO_TEST_CASE( writeAndReadJson )
{
    std::string name = "moehre";
    std::vector<double> nutrition {1.2, 100, 204};
    double min = 4.332;
    double max = 3.22;

    Food foodIn{name, std::move(nutrition), min, max};
    Json::Value foodObj = foodIn.toJson();
    
    Food foodOut;
    foodOut.readFromJson(foodObj);

    BOOST_TEST( foodOut == foodIn );
}

BOOST_AUTO_TEST_SUITE_END( )


BOOST_AUTO_TEST_SUITE( decorator )

BOOST_AUTO_TEST_CASE( ApplyFirstValuedThenAnalyzedDecorator )
{
    double amount{3.1};
    double cost{400};

    std::unique_ptr<Food> food = std::make_unique<Food>("himbeere");
    food = std::make_unique<Valued>(std::move(food), cost);
    food = std::make_unique<Analyzed>(std::move(food), amount);

    BOOST_TEST( food->getCost() == cost );
    BOOST_TEST( food->getAmount() == amount );
}

BOOST_AUTO_TEST_CASE( ApplyFirstAnlyzedThenValuedDecorator )
{
    double amount{3.1};
    double cost{400};

    std::unique_ptr<Food> food = std::make_unique<Food>("himbeere");
    food = std::make_unique<Analyzed>(std::move(food), amount);
    food = std::make_unique<Valued>(std::move(food), cost);

    BOOST_TEST( food->getCost() == cost );
    BOOST_TEST( food->getAmount() == amount );
}

BOOST_AUTO_TEST_SUITE_END( )
