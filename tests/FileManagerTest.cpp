#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../lib/include/FileManager.h"
#include "../lib/include/Utilities.h"

TEST_CASE("Life, the universe and everything") {
    REQUIRE(7*6 == 42);
}
TEST_CASE("Split string") {
    SECTION("NR") {
        std::vector<std::string> vec = Utilities::splitString("abcdefgh\n\raaaaaaaa\n\rbbbbbbbb");
        REQUIRE(vec[0] == "abcdefgh");
        REQUIRE(vec[1] == "aaaaaaaa");
        REQUIRE(vec[2] == "bbbbbbbb");
    }
    SECTION("N") {
        std::vector<std::string> vec = Utilities::splitString("abcdefgh\naaaaaaaa\nbbbbbbbb");
        REQUIRE(vec[0] == "abcdefgh");
        REQUIRE(vec[1] == "aaaaaaaa");
        REQUIRE(vec[2] == "bbbbbbbb");
    }
    SECTION("R") {
        std::vector<std::string> vec = Utilities::splitString("abcdefgh\raaaaaaaa\rbbbbbbbb");
        REQUIRE(vec[0] == "abcdefgh");
        REQUIRE(vec[1] == "aaaaaaaa");
        REQUIRE(vec[2] == "bbbbbbbb");
    }
    SECTION("RN") {
        std::vector<std::string> vec = Utilities::splitString("abcdefgh\r\naaaaaaaa\r\nbbbbbbbb");
        REQUIRE(vec[0] == "abcdefgh");
        REQUIRE(vec[1] == "aaaaaaaa");
        REQUIRE(vec[2] == "bbbbbbbb");
    }
}

TEST_CASE("Write to file") {
    system("cp ../tests/resources/test.txt ../tests/resources/test3.txt ");
    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;
    FileManager fileManager("../tests/resources/test3.txt");
    REQUIRE(fileManager.readFile() == "abcdefgh");
}

TEST_CASE("File manager") {
    SECTION("Loads file") {
        FileManager fileManager("../tests/resources/fm_test.txt");
        REQUIRE(fileManager.readFile() == "abcdefgh");
    }
    SECTION("Loads file and split") {
        FileManager fileManager("../tests/resources/fm_test2.txt");
        std::vector<std::string> vec = Utilities::splitString(fileManager.readFile());
        REQUIRE(vec[0] == "abcdefgh");
        REQUIRE(vec[1] == "save_test");
    }
    SECTION("Remove line from file") {
        system("cp ../tests/resources/fm_test2.txt ../tests/resources/fm_test4.txt ");

        FileManager fileManager("../tests/resources/fm_test4.txt");
        std::vector<std::string> vec = Utilities::splitString(fileManager.readFile());
        vec.erase(vec.begin() + 1);

        fileManager.writeFile(vec);
        std::vector<std::string> resultVec = Utilities::splitString(fileManager.readFile());
        REQUIRE(resultVec[0] == "abcdefgh");
        REQUIRE(resultVec[1] == "bbbbbbbb");
    }
}