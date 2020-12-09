#include "../cs225/catch/catch.hpp"
#include "../degree.h"
#include "../landmarkpath.h"

#include <iostream>

TEST_CASE("sanity_check", "[valgrind][weight=1][landmarkpath]") {
    REQUIRE(3==3);
}

TEST_CASE("small file", "[valgrind][weight=1][landmarkpath]") {
    degree d("tests/small_routedata.txt", "tests/small_airport_data.txt");
    d.readFromAirport();

    REQUIRE(!d.getLocations().empty());

    std::unordered_map<std::string, std::pair<double, double>> locations = d.getLocations();
    LandmarkPath lp("tests/small_routedata.txt", locations);
    Graph g = lp.getGraph();

    SECTION("check if graph is right") {
        REQUIRE(!g.getVertices().empty());
        REQUIRE(g.vertexExists("AAA"));
        REQUIRE(g.edgeExists("AAA", "BBB"));
    }


    SECTION("test getShortestPath") {
        std::vector<std::string> expected_result;
        expected_result.push_back("CCC");
        expected_result.push_back("BBB");
        expected_result.push_back("AAA");
        REQUIRE(lp.getShortestPath("AAA", "CCC") == expected_result);
    }

    SECTION("test landmarkpath test") {
        std::vector<std::string> expected_result;
        expected_result.push_back("FFF");
        expected_result.push_back("EEE");
        expected_result.push_back("CCC");
        expected_result.push_back("BBB");
        expected_result.push_back("AAA");
        REQUIRE(lp.getResult("AAA", "CCC" , "KKK") == expected_result);
    }
}





