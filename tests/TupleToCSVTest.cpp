#include "../lib/include/Tuple.h"
#include "../lib/include/Parser.h"
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
TEST_CASE("Check toPattern()") {
    SECTION("Test 1 - simple entities") {
        Tuple tuple = Tuple(std::vector<Entity>{
                Entity(1),
                Entity("2"),
                Entity(3.1),
                Entity(4),
        });

        std::string result = tuple.toPattern();
        std::string correctCSV = "integer:=1,string:=\"2\",float:=3.1,integer:=4";
        REQUIRE(result == correctCSV);
    }
    SECTION("Test 2 - operators") {
        Tuple tuple = Tuple(std::vector<Entity>{
                Entity(1, MORE),
                Entity("2", LESS),
                Entity(3.1, EQ_MORE),
                Entity(4, EQ_LESS),
        });

        std::string result = tuple.toPattern();
        std::string correctCSV = "integer:>1,string:<\"2\",float:>=3.1,integer:<=4";
        REQUIRE(result == correctCSV);
    }
    SECTION("Test 3 - ANY") {
        Tuple tuple = Tuple(std::vector<Entity>{
                Entity(INT),
                Entity(FLOAT),
                Entity(STR),
        });

        std::string result = tuple.toPattern();
        std::string correctCSV = "integer:*,float:*,string:*";
        REQUIRE(result == correctCSV);
    }
}

TEST_CASE("Check toFilePattern()") {
    Tuple tuple = Tuple(std::vector<Entity>{
            Entity(1),
            Entity("2"),
            Entity(3.1),
            Entity(4),
    });
    tuple.setSemKey(12121212);

    std::string result = tuple.toFilePattern();
    std::string correctCSV = "12121212,integer:=1,string:=\"2\",float:=3.1,integer:=4";
    REQUIRE(result == correctCSV);
}

TEST_CASE("Reverse tests (parsing and converting to strings)") {
    SECTION("Test 1 - toCSV") {
        Tuple tuple = Tuple(std::vector<Entity>{
                Entity(1),
                Entity("2"),
                Entity(3.1),
                Entity(4),
        });

        std::string result = tuple.toCSV();
        std::string correctCSV = "1,\"2\",3.1,4";
        REQUIRE(result == correctCSV);

        Parser parser = Parser();
        Tuple *resultTuple = parser.parseCSV(result);

        REQUIRE(*resultTuple == tuple);
    }
    SECTION("Test 2 - toPattern") {
        Tuple tuple = Tuple(std::vector<Entity>{
                Entity(1),
                Entity("2"),
                Entity(3.1),
                Entity(4),
        });

        std::string result = tuple.toPattern();
        std::string correctCSV = "integer:=1,string:=\"2\",float:=3.1,integer:=4";
        REQUIRE(result == correctCSV);

        Parser parser = Parser();
        Tuple *resultTuple = parser.parsePattern(result);

        REQUIRE(*resultTuple == tuple);
    }
    SECTION("Test 3 - toFilePattern") {
        Tuple tuple = Tuple(std::vector<Entity>{
                Entity(1),
                Entity("2"),
                Entity(3.1),
                Entity(4),
        });
        tuple.setSemKey(12121212);

        std::string result = tuple.toFilePattern();
        std::string correctCSV = "12121212,integer:=1,string:=\"2\",float:=3.1,integer:=4";
        REQUIRE(result == correctCSV);

        Parser parser = Parser();
        Tuple *resultTuple = parser.parseFilePattern(result);

        REQUIRE(*resultTuple == tuple);
    }
}
