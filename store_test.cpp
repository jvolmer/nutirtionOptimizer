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

BOOST_AUTO_TEST_CASE( computeFoodPlan )
{
    Store store("Kueche");
    store.addFood({"Eiweiss", {1, 0, 0}, 0, 1000});
    store.addFood({"MUFA", {0, 1, 0}, 0, 1000});
    store.addFood({"Eicosapentaensaeure", {0, 0, 1}, 0, 1000});
 
    Person julia("Julia");
    julia.setNutritionMinima({1, 1, 1});

    store.computeFoodPlan(julia);

    std::vector<double> expectedValue{1, 1, 1};

    const std::vector<Food>& foodVec = store.getFood();
    for (unsigned i=0;i < foodVec.size(); i++)
        BOOST_TEST( foodVec[i].getAmount() == expectedValue[i] );
}

BOOST_AUTO_TEST_SUITE_END( )
