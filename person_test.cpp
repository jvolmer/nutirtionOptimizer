#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE persontest
#include <boost/test/unit_test.hpp>
#include <vector>
#include <fstream>
#include "person.hpp"

BOOST_AUTO_TEST_SUITE( persontest )

BOOST_AUTO_TEST_CASE( testReadAndWrite, * boost::unit_test::tolerance(1e-10) )
{
    // create user
    NutritionDemandingUser user{"julia"};
    std::vector<double> nutritionsIn{1.43, 5.3, 99.2};
    user.setNutritionMinima(nutritionsIn);

    // write user to file
    std::ofstream fileIn("person.out");
    fileIn << user.toJson();
    fileIn.close();

    // read user from file
    std::ifstream fileOut("person.out");
    Json::Value fileContent;
    fileOut >> fileContent;
    user.readFromJson(fileContent);

    // test
    const std::vector<double>& nutritionsOut = user.getNutritionMinima();

    BOOST_TEST( nutritionsIn == nutritionsOut, boost::test_tools::per_element() );
}

BOOST_AUTO_TEST_SUITE_END( )
