#include "catch.hpp"
#include "../lib/include/tuple.h"

TEST_CASE("Get TypedEntity value") {
    TypedEntity<int> intEntity = TypedEntity<int>(1);
    REQUIRE(intEntity.getValue() == 1);
    TypedEntity<double> doubleEntity = TypedEntity<double>(1.1);
    REQUIRE(doubleEntity.getValue() == 1.1);
    TypedEntity<std::string> stringEntity = TypedEntity<std::string>("test");
    REQUIRE(stringEntity.getValue() == "test");
}
TEST_CASE("Compare TypedEntity types") {
    TypedEntity<int> intEntity = TypedEntity<int>(1);
    TypedEntity<double> doubleEntity = TypedEntity<double>(1.1, EQUAL);
    REQUIRE(doubleEntity.compare(intEntity) == false);
}