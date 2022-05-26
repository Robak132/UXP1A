#include "../lib/include/tuple.h"
#include "../lib/include/linda.h"
#include "catch.hpp"

Tuple testTuple1 = Tuple(std::vector<Entity> {
        Entity::createIntEntity(1),
        Entity::createStringEntity("abc"),
        Entity::createDoubleEntity(3.1415),
        Entity::createStringEntity("d"),
});
Tuple testTuple2 = Tuple(std::vector<Entity> {
        Entity::createIntEntity(1),
        Entity::createStringEntity("abc"),
        Entity::createDoubleEntity(3.1415),
});
Tuple testTuple3 = Tuple(std::vector<Entity> {
        Entity::createIntEntity(2),
        Entity::createIntEntity(3),
        Entity::createIntEntity(1),
        Entity::createStringEntity("Ala ma kota"),
});

TEST_CASE("Linda output") {
    system("rm ../tests/resources/data.csv");
    system("rm ../tests/resources/processes.csv");

    Linda linda = Linda("../tests/resources/data.csv", "../tests/resources/processes.csv");
    linda.output(testTuple1);

    FileManager fileManager("../tests/resources/data.csv");
    REQUIRE(fileManager.readFile() == R"(1,"abc",3.1415,"d")");
}
TEST_CASE("Linda input") {
    system("cp ../tests/resources/linda_test_data.csv ../tests/resources/data.csv");
    system("rm ../tests/resources/processes.csv");

    Tuple templateTuple = Tuple(std::vector<Entity> {
            Entity::createIntEntity(1),
            Entity::createStringEntity("", ANY),
            Entity::createDoubleEntity(0, ANY),
            Entity::createStringEntity("d"),
    });

    auto* mockParser = new MockParser({testTuple1, testTuple2, testTuple3});

    Linda linda = Linda(
            "../tests/resources/data.csv",
            "../tests/resources/processes.csv",
            mockParser);
    Tuple* result = linda.input(templateTuple);
    REQUIRE(result->compare(testTuple1));

    FileManager fileManager("../tests/resources/data.csv");
    REQUIRE(fileManager.readFile() == "10,\"abc\",3.1415,\n2,3,1,\"Ala ma kota\"");

    delete result;
}
TEST_CASE("Linda read") {
    system("cp ../tests/resources/linda_test_data.csv ../tests/resources/data.csv");
    system("rm ../tests/resources/processes.csv");

    Tuple templateTuple = Tuple(std::vector<Entity> {
            Entity::createIntEntity(1),
            Entity::createStringEntity("", ANY),
            Entity::createDoubleEntity(0, ANY),
            Entity::createStringEntity("d"),
    });

    auto* mockParser = new MockParser({testTuple1, testTuple2, testTuple3});

    Linda linda = Linda(
            "../tests/resources/data.csv",
            "../tests/resources/processes.csv",
            mockParser);
    Tuple* result = linda.read(templateTuple);
    REQUIRE(result->compare(testTuple1));

    FileManager fileManager("../tests/resources/data.csv");
    std::string dataString = fileManager.readFile();
    std::string expected = "1,\"abc\",3.1415,\"d\"\r\n10,\"abc\",3.1415,\r\n2,3,1,\"Ala ma kota\"";
    for (int i=0;i<expected.size();i++) {
        std::cout << i << ": " << (dataString[i] == expected[i]) << std::endl;
    }

    delete result;
}