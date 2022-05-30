cmake_minimum_required(VERSION 3.16)
project(main)

set(CMAKE_CXX_STANDARD 20)

add_executable(writelock lib/src/example/writelock.cpp)
add_executable(readlock lib/src/example/readlock.cpp)
add_executable(lindatest
        lib/src/Main.cpp
        lib/src/Linda.cpp
        lib/src/FileManager.cpp
        lib/src/Tuple.cpp
        lib/src/Entity.cpp
        lib/src/Parser.cpp)

set(url https://github.com/philsquared/Catch/releases/download/v2.13.6/catch.hpp)
file(
        DOWNLOAD ${url} "${CMAKE_CURRENT_BINARY_DIR}/catch.hpp"
        STATUS status
        EXPECTED_HASH SHA256=681e7505a50887c9085539e5135794fc8f66d8e5de28eadf13a30978627b0f47)
list(GET status 0 error)
if(error)
    message(FATAL_ERROR "Could not download ${url}")
endif()

add_executable(CatchTests
        tests/FileManagerTest.cpp
        tests/TupleCompareTest.cpp
        tests/TupleToCSVTest.cpp
        tests/LindaMainTest.cpp
        tests/ParserTest.cpp

        lib/src/Tuple.cpp
        lib/src/Entity.cpp
        lib/src/Linda.cpp
        lib/src/Parser.cpp
        lib/src/FileManager.cpp
        lib/src/Utilities.cpp)
target_include_directories(CatchTests PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")
