#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE storetest
#include <boost/test/unit_test.hpp>
#include "store.hpp"
#include "food.hpp"

BOOST_AUTO_TEST_SUITE (storetest)

BOOST_AUTO_TEST_CASE( addFood )
{
    std::vector<double> nutrition{100, 20, 1.3};
    Food testFoodIn{"apfel", nutrition, 1, 3};

    Store newStore{"kueche"};
    newStore.addFood(testFoodIn);
    const std::vector<Food>& foodVector = newStore.getFood();
    const Food& testFoodOut = foodVector.back();
    
    BOOST_CHECK(testFoodOut == testFoodIn);
}

BOOST_AUTO_TEST_SUITE_END( )
