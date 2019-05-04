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

    FoodStore newStore{"kueche"};
    newStore.addGood(testFoodIn);
    const std::vector<Food>& foodVector = newStore.getAllGoods();
    const Food& testFoodOut = foodVector.back();

    BOOST_TEST( foodVector.size() == 1 );
    BOOST_TEST( testFoodOut == testFoodIn );
}

BOOST_AUTO_TEST_CASE( addTwoFoods )
{
    Food testFoodIn1{"test1"};
    Food testFoodIn2{"test2"};
    
    FoodStore newStore{"kueche"};
    newStore.addGood(testFoodIn1);
    newStore.addGood(testFoodIn2);
    const std::vector<Food>& foodVector = newStore.getAllGoods();
    const Food& testFoodOut1 = foodVector.front();
    const Food& testFoodOut2 = foodVector.back();

    BOOST_TEST( foodVector.size() == 2 );
    BOOST_TEST( testFoodOut1 == testFoodIn1 );
    BOOST_TEST( testFoodOut2 == testFoodIn2 );
}

BOOST_AUTO_TEST_CASE( testReadAndWrite )
{
    FoodStore store{"testStore", "test.out"};

    Food foodIn{"testFood", {3.221, 4.3, 9.99992}, 4.3, 999.91};
    store.addGood(std::move(foodIn));
    store.write();

    store.clearFood();
    store.read();
    const std::vector<Food>& foodVector = store.getAllGoods();    
    const Food& foodOut = foodVector.back();

    BOOST_TEST( foodVector.size() == 1 );
    BOOST_TEST( foodOut == foodIn );
}

BOOST_AUTO_TEST_SUITE_END( )
