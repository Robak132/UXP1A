#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../lib/include/FileManager.h"
#include "../lib/include/Utilities.h"

TEST_CASE("Life, the universe and everything") {
    REQUIRE(7*6 == 42);
}
TEST_CASE("Split string") {
    std::vector<std::string> vec = Utilities::splitString("abcdefgh\n\raaaaaaaa\n\rbbbbbbbb");
    REQUIRE(vec[0] == "abcdefgh");
    REQUIRE(vec[1] == "aaaaaaaa");
    REQUIRE(vec[2] == "bbbbbbbb");
}
TEST_CASE("Loads file") {
    FileManager fileManager("../tests/resources/fm_test.txt");
    REQUIRE(fileManager.readFile() == "abcdefgh");
}
TEST_CASE("Loads file and split") {
    FileManager fileManager("../tests/resources/fm_test2.txt");
    std::vector<std::string> vec = Utilities::splitString(fileManager.readFile());
    REQUIRE(vec[0] == "abcdefgh");
    REQUIRE(vec[1] == "aaaaaaaa");
    REQUIRE(vec[2] == "bbbbbbbb");
}
TEST_CASE("Append line to file") {
    system("cp ../tests/resources/fm_test.txt ../tests/resources/fm_test3.txt ");
    FileManager fileManager("../tests/resources/fm_test3.txt");
    fileManager.appendLine("save_test");

    std::vector<std::string> vec = Utilities::splitString(fileManager.readFile());
    REQUIRE(vec[0] == "abcdefgh");
    REQUIRE(vec[1] == "save_test");
}
TEST_CASE("Remove line from file") {
    system("cp ../tests/resources/fm_test2.txt ../tests/resources/fm_test4.txt ");

    FileManager fileManager("../tests/resources/fm_test4.txt");
    std::vector<std::string> vec = Utilities::splitString(fileManager.readFile());
    vec.erase(vec.begin()+1);

    fileManager.writeFile(vec);
    std::vector<std::string> resultVec = Utilities::splitString(fileManager.readFile());
    REQUIRE(resultVec[0] == "abcdefgh");
    REQUIRE(resultVec[1] == "bbbbbbbb");
}
