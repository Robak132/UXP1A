#include "../lib/include/tuple.h"
#include "catch.hpp"

TEST_CASE("Check toCSV()") {
    Tuple tuple = Tuple(std::vector<Entity> {
            Entity::createIntEntity(1),
            Entity::createStringEntity("2"),
            Entity::createDoubleEntity(3.1),
            Entity::createIntEntity(4),
    });

    std::string result = tuple.toCSV();
    std::string correctCSV = "1,\"2\",3.1,4";
    REQUIRE(result == correctCSV);
}

TEST_CASE("Check toCSV() 2") {
    Tuple tuple = Tuple(std::vector<Entity> {
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

