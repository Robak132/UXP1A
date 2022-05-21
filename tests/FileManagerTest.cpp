#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../lib/include/file_manager.h"

TEST_CASE("Life, the universe and everything") {
    REQUIRE(7*6 == 42);
}
TEST_CASE("Loads file") {
    FileManager fileManager("../tests/resources/test.txt");
    REQUIRE(fileManager.readFile() == "abcdefgh");
}
TEST_CASE("Loads file and split") {
    FileManager fileManager("../tests/resources/test2.txt");
    std::vector<std::string> vec = fileManager.readSplitFile();
    REQUIRE(vec[0] == "abcdefgh");
    REQUIRE(vec[1] == "aaaaaaaa");
    REQUIRE(vec[2] == "bbbbbbbb");
}
