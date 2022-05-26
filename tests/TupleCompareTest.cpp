#include "catch.hpp"
#include "../lib/include/Tuple.h"

TEST_CASE("Get Entity value") {
    Entity intEntity = Entity::createIntEntity(1);
    REQUIRE(intEntity.getIntValue() == 1);
    Entity doubleEntity = Entity::createDoubleEntity(1.1);
    REQUIRE(doubleEntity.getDoubleValue() == 1.1);
    Entity stringEntity = Entity::createStringEntity("test");
    REQUIRE(stringEntity.getStringValue() == "test");
}
TEST_CASE("Compare Entity types") {
    Entity intEntity = Entity::createIntEntity(1);
    Entity doubleEntity = Entity::createDoubleEntity(1.1, EQUAL);
    REQUIRE(doubleEntity.compare(intEntity) == false);
}
TEST_CASE("Compare Tuple: good") {
    Tuple tuple = Tuple(std::vector<Entity>{
            Entity::createIntEntity(1),
            Entity::createStringEntity("abc"),
            Entity::createDoubleEntity(3.1415),
            Entity::createStringEntity("d"),
    });
    SECTION("Basic") {
        Tuple patternTuple = Tuple(std::vector<Entity>{
                Entity::createIntEntity(1),
                Entity::createStringEntity("abc"),
                Entity::createDoubleEntity(3.1415),
                Entity::createStringEntity("d"),
        });
        REQUIRE(patternTuple.compare(tuple));
    }
    SECTION("Advanced") {
        Tuple patternTuple = Tuple(std::vector<Entity>{
                Entity::createIntEntity(1),
                Entity::createStringEntity("", ANY),
                Entity::createDoubleEntity(0, ANY),
                Entity::createStringEntity("d"),
        });
        REQUIRE(patternTuple.compare(tuple));
    }
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
TEST_CASE("Compare Entity: operators") {
    Entity testEntity = Entity::createIntEntity(10);
    SECTION("EQUAL") {
        Entity patternEntity = Entity::createIntEntity(10);
        Entity patternEntity2 = Entity::createIntEntity(5);
        REQUIRE(patternEntity.compare(testEntity, EQUAL));
        REQUIRE(!patternEntity2.compare(testEntity, EQUAL));
    }
    SECTION("LESS") {
        Entity patternEntity = Entity::createIntEntity(5);
        Entity patternEntity2 = Entity::createIntEntity(15);
        REQUIRE(patternEntity.compare(testEntity, LESS));
        REQUIRE(!patternEntity2.compare(testEntity, LESS));
    }
    SECTION("MORE") {
        Entity patternEntity = Entity::createIntEntity(15);
        Entity patternEntity2 = Entity::createIntEntity(5);
        REQUIRE(patternEntity.compare(testEntity, MORE));
        REQUIRE(!patternEntity2.compare(testEntity, MORE));
    }
    SECTION("EQ_LESS") {
        Entity patternEntity = Entity::createIntEntity(10);
        Entity patternEntity2 = Entity::createIntEntity(5);
        Entity patternEntity3 = Entity::createIntEntity(15);
        REQUIRE(patternEntity.compare(testEntity, EQ_LESS));
        REQUIRE(patternEntity2.compare(testEntity, EQ_LESS));
        REQUIRE(!patternEntity3.compare(testEntity, EQ_LESS));
    }
    SECTION("EQ_MORE") {
        Entity patternEntity = Entity::createIntEntity(10);
        Entity patternEntity2 = Entity::createIntEntity(5);
        Entity patternEntity3 = Entity::createIntEntity(15);
        REQUIRE(patternEntity.compare(testEntity, EQ_MORE));
        REQUIRE(!patternEntity2.compare(testEntity, EQ_MORE));
        REQUIRE(patternEntity3.compare(testEntity, EQ_MORE));
    }
    SECTION("ANY") {
        Entity patternEntity = Entity::createIntEntity(-10);
        Entity patternEntity2 = Entity::createIntEntity(10);
        REQUIRE(patternEntity.compare(testEntity, ANY));
        REQUIRE(patternEntity2.compare(testEntity, ANY));
    }
}