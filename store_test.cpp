#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE storetest
#include <boost/test/unit_test.hpp>
#include "store.hpp"
#include "food.hpp"

BOOST_AUTO_TEST_SUITE (storetest)

BOOST_AUTO_TEST_CASE( addOneFood )
{
    Food testFoodIn{"test"};
    
    Store newStore{"kueche"};
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
    
    Store newStore{"kueche"};
    newStore.addGood(testFoodIn1);
    newStore.addGood(testFoodIn2);
    const std::vector<Food>& foodVector = newStore.getAllGoods();
    const Food& testFoodOut1 = foodVector.front();
    const Food& testFoodOut2 = foodVector.back();

    BOOST_TEST( foodVector.size() == 2 );
    BOOST_TEST( testFoodOut1 == testFoodIn1 );
    BOOST_TEST( testFoodOut2 == testFoodIn2 );
}

BOOST_AUTO_TEST_SUITE_END( )
