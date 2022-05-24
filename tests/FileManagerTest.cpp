#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../lib/include/file_manager.h"

TEST_CASE("Life, the universe and everything") {
    REQUIRE(7*6 == 42);
}
TEST_CASE("Loads file") {
    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;
    FileManager fileManager("../tests/resources/test.txt", lock);
    REQUIRE(fileManager.readFile() == "abcdefgh");
}
TEST_CASE("Loads file and split") {
    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;
    FileManager fileManager("../tests/resources/test2.txt", lock);
    std::vector<std::string> vec = fileManager.readSplitFile();
    REQUIRE(vec[0] == "abcdefgh");
    REQUIRE(vec[1] == "aaaaaaaa");
    REQUIRE(vec[2] == "bbbbbbbb");
}
TEST_CASE("Write to file") {
    system("cp ../tests/resources/test.txt ../tests/resources/test3.txt ");
    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;
    FileManager fileManager("../tests/resources/test3.txt", lock);
    REQUIRE(fileManager.readFile() == "abcdefgh");

    fileManager.writeLine("save_test");
    std::vector<std::string> vec = fileManager.readSplitFile();
    REQUIRE(vec[0] == "abcdefgh");
    REQUIRE(vec[1] == "save_test");
}
