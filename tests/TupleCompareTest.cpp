#include "catch.hpp"
#include "../lib/include/tuple.h"

TEST_CASE("Get TypedEntity value") {
    Entity intEntity = Entity::createIntEntity(1);
    REQUIRE(intEntity.getIntValue() == 1);
    Entity doubleEntity = Entity::createDoubleEntity(1.1);
    REQUIRE(doubleEntity.getDoubleValue() == 1.1);
    Entity stringEntity = Entity::createStringEntity("test");
    REQUIRE(stringEntity.getStringValue() == "test");
}
TEST_CASE("Compare TypedEntity types") {
    Entity intEntity = Entity::createIntEntity(1);
    Entity doubleEntity = Entity::createDoubleEntity(1.1, EQUAL);
    REQUIRE(doubleEntity.compare(intEntity) == false);
}
TEST_CASE("Compare Tuple: good") {
    Tuple tuple1 = Tuple(std::vector<Entity> {
            Entity::createIntEntity(1),
            Entity::createStringEntity("2"),
            Entity::createDoubleEntity(3.1),
            Entity::createIntEntity(4),
    });
    Tuple tuple2 = Tuple(std::vector<Entity> {
            Entity::createIntEntity(1),
            Entity::createStringEntity("2"),
            Entity::createDoubleEntity(3.1),
            Entity::createIntEntity(4),
    });
    REQUIRE(tuple1.compare(tuple2) == true);
}
TEST_CASE("Compare Tuple: wrong size") {
    Tuple tuple1 = Tuple(std::vector<Entity> {
            Entity::createIntEntity(1),
            Entity::createIntEntity(2),
            Entity::createIntEntity(3),
            Entity::createIntEntity(4),
    });
    Tuple tuple2 = Tuple(std::vector<Entity> {
            Entity::createIntEntity(1),
            Entity::createIntEntity(2),
    });
    REQUIRE(tuple1.compare(tuple2) == false);
}
TEST_CASE("Compare Tuple: wrong types") {
    Tuple tuple1 = Tuple(std::vector<Entity> {
            Entity::createIntEntity(1),
            Entity::createIntEntity(2),
            Entity::createIntEntity(3),
            Entity::createIntEntity(4),
    });
    Tuple tuple2 = Tuple(std::vector<Entity> {
            Entity::createIntEntity(1),
            Entity::createDoubleEntity(2),
            Entity::createStringEntity("3"),
            Entity::createIntEntity(4),
    });
    REQUIRE(tuple1.compare(tuple2) == false);
}