#include "../lib/include/Tuple.h"
#include "../lib/include/Linda.h"
#include "catch.hpp"

TEST_CASE("Main functions") {
    Tuple testTuple1 = Tuple(std::vector<Entity>{
            Entity::createIntEntity(1),
            Entity::createStringEntity("abc"),
            Entity::createDoubleEntity(3.1415),
            Entity::createStringEntity("d"),
    });
    Tuple testTuple2 = Tuple(std::vector<Entity>{
            Entity::createIntEntity(1),
            Entity::createStringEntity("abc"),
            Entity::createDoubleEntity(3.1415),
    });
    Tuple testTuple3 = Tuple(std::vector<Entity>{
            Entity::createIntEntity(2),
            Entity::createIntEntity(3),
            Entity::createIntEntity(1),
            Entity::createStringEntity("Ala ma kota"),
    });
    SECTION("Output") {
        system("rm ../tests/resources/data.csv");
        system("rm ../tests/resources/processes.csv");

        Linda linda = Linda("../tests/resources/data.csv", "../tests/resources/processes.csv");
        linda.output(testTuple1);

        FileManager fileManager("../tests/resources/data.csv");
        REQUIRE(fileManager.readFile() == R"(1,"abc",3.1415,"d")");
    }

    SECTION("Input Mock") {
        system("cp ../tests/resources/linda_test_data.csv ../tests/resources/data.csv");
        system("rm ../tests/resources/processes.csv");

        Tuple templateTuple = Tuple(std::vector<Entity>{
                Entity::createIntEntity(1),
                Entity::createStringEntity(),
                Entity::createDoubleEntity(),
                Entity::createStringEntity("d"),
        });

        auto *mockParser = new MockParser({testTuple1, testTuple2, testTuple3});

        Linda linda = Linda(
                "../tests/resources/data.csv",
                "../tests/resources/processes.csv",
                mockParser);
        Tuple *result = linda.input(templateTuple);
        FileManager fileManager("../tests/resources/data.csv");
        REQUIRE(result ->compare(testTuple1));


        std::vector<std::string> readFileResult = Utilities::splitString(fileManager.readFile());
        std::string correctString = "10,\"abc\",3.1415,\r\n2,3,1,\"Ala ma kota\"";
        std::vector<std::string> correctVector = Utilities::splitString(correctString);

        REQUIRE(readFileResult == correctVector);

        delete result;
    }
    SECTION("Input Proper") {
        system("cp ../tests/resources/linda_test_data.csv ../tests/resources/data.csv");
        system("rm ../tests/resources/processes.csv");


        Linda linda = Linda(
                "../tests/resources/data.csv",
                "../tests/resources/processes.csv");
        Tuple *result = linda.input(R"(integer:1, string:*, float:*, string:"d")");
        REQUIRE(result->compare(testTuple1));

        FileManager fileManager("../tests/resources/data.csv");

        std::vector<std::string> readFileResult = Utilities::splitString(fileManager.readFile());
        std::string correctString = "10,\"abc\",3.1415,\r\n2,3,1,\"Ala ma kota\"";
        std::vector<std::string> correctVector = Utilities::splitString(correctString);

        REQUIRE(readFileResult == correctVector);

        delete result;
    }

    SECTION("Read Mock") {
        system("cp ../tests/resources/linda_test_data.csv ../tests/resources/data.csv");
        system("rm ../tests/resources/processes.csv");

        Tuple templateTuple = Tuple(std::vector<Entity>{
                Entity::createIntEntity(1),
                Entity::createStringEntity("", ANY),
                Entity::createDoubleEntity(0, ANY),
                Entity::createStringEntity("d"),
        });

        auto *mockParser = new MockParser({testTuple1, testTuple2, testTuple3});

        Linda linda = Linda(
                "../tests/resources/data.csv",
                "../tests/resources/processes.csv",
                mockParser);
        Tuple *result = linda.read(templateTuple);
        REQUIRE(result->compare(testTuple1));

        FileManager fileManager("../tests/resources/data.csv");

        std::vector<std::string> readFileResult = Utilities::splitString(fileManager.readFile());
        std::string correctString = "1,\"abc\",3.1415,\"d\"\r\n10,\"abc\",3.1415,\r\n2,3,1,\"Ala ma kota\"";
        std::vector<std::string> correctVector = Utilities::splitString(correctString);

        REQUIRE(readFileResult == correctVector);

        delete result;
    }
    SECTION("Read Proper") {
        system("cp ../tests/resources/linda_test_data.csv ../tests/resources/data.csv");
        system("rm ../tests/resources/processes.csv");

        Linda linda = Linda(
                "../tests/resources/data.csv",
                "../tests/resources/processes.csv");
        Tuple *result = linda.read(R"(integer:1, string:*, float:*, string:"d")");
        REQUIRE(result->compare(testTuple1));

        FileManager fileManager("../tests/resources/data.csv");

        std::vector<std::string> readFileResult = Utilities::splitString(fileManager.readFile());
        std::string correctString = "1,\"abc\",3.1415,\"d\"\r\n10,\"abc\",3.1415,\r\n2,3,1,\"Ala ma kota\"";
        std::vector<std::string> correctVector = Utilities::splitString(correctString);

        REQUIRE(readFileResult == correctVector);

        delete result;
    }
}