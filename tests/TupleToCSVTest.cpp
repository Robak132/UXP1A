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

