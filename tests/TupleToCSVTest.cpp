#include "../lib/include/Tuple.h"
#include "catch.hpp"

TEST_CASE("Check toCSV()") {
    SECTION("Test 1 - simple ventities") {
        Tuple tuple = Tuple(std::vector<Entity>{
                Entity::createIntEntity(1),
                Entity::createStringEntity("2"),
                Entity::createDoubleEntity(3.1),
                Entity::createIntEntity(4),
        });

        std::string result = tuple.toCSV();
        std::string correctCSV = "1,\"2\",3.1,4";
        REQUIRE(result == correctCSV);
    }
    SECTION("Test 2 - large entities") {
        Tuple tuple = Tuple(std::vector<Entity>{
                Entity::createIntEntity(1),
                Entity::createStringEntity("How much wood would a woodchuck chuck?"),
                Entity::createStringEntity("2,200"),
                Entity::createStringEntity("Defenestration"),
                Entity::createDoubleEntity(3.14159),
                Entity::createIntEntity(40000000),
        });

        std::string result = tuple.toCSV();
        std::string correctCSV = R"(1,"How much wood would a woodchuck chuck?","2,200","Defenestration",3.14159,40000000)";
        REQUIRE(result == correctCSV);
    }
    SECTION("Test 3 - string escaping") {
        Tuple tuple = Tuple(std::vector<Entity>{
                Entity::createIntEntity(1),
                Entity::createStringEntity("How much wood \"would\" a woodchuck chuck?"),
                Entity::createStringEntity("2,200\\\\"),
                Entity::createStringEntity("Defenestration\n"),
        });

        std::string result = tuple.toCSV();
        std::string correctCSV = "1,\"How much wood \"would\" a woodchuck chuck?\",\"2,200\\\\\",\"Defenestration\n\"";
        REQUIRE(result == correctCSV);
    }
}