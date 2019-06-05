#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE storetest
#include <boost/test/unit_test.hpp>
#include <utility>
#include "store.hpp"
#include "food.hpp"

BOOST_AUTO_TEST_SUITE (storetest)

BOOST_AUTO_TEST_CASE( addOneFood )
{
    Food testFoodIn{"test"};

    FoodStore store{"kueche"};
    store.addGood(testFoodIn);

    BOOST_TEST( store.getNumberOfFoods() == 1);
    BOOST_TEST( store.containsFoodAtPosition(0, testFoodIn) );
}

BOOST_AUTO_TEST_CASE( addTwoFoods )
{
    Food testFoodIn1{"test1"};
    Food testFoodIn2{"test2"};
    
    FoodStore store{"kueche"};
    store.addGood(testFoodIn1);
    store.addGood(testFoodIn2);

    BOOST_TEST( store.getNumberOfFoods() == 2 );
    BOOST_TEST( store.containsFoodAtPosition(0, testFoodIn1) );
    BOOST_TEST( store.containsFoodAtPosition(1, testFoodIn2) );
}

BOOST_AUTO_TEST_CASE( testReadAndWrite )
{
    // create store
    FoodStore store{"testStore"};
    Food foodIn{"testFood", {3.221, 4.3, 9.99992}, 4.3, 999.91};
    store.addGood(foodIn);

    // write store to file
    std::ofstream fileIn("test.out");
    fileIn << store.toJson();
    fileIn.close();

    // clear store
    store.clearFood();

    //read store from file
    std::ifstream fileOut("test.out");    
    Json::Value fileContent;
    fileOut >> fileContent;
    store.readFromJson(fileContent);

    // test
    BOOST_TEST( store.getNumberOfFoods() == 1 );
    BOOST_TEST( store.containsFoodAtPosition(0, foodIn) );
}

BOOST_AUTO_TEST_SUITE_END( )

