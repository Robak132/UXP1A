cmake_minimum_required(VERSION 3.16)
project(main)

set(CMAKE_CXX_STANDARD 14)

add_executable(writelock lib/src/example/writelock.cpp)
add_executable(readlock lib/src/example/readlock.cpp)
add_executable(lindatest
        lib/src/main.cpp
        lib/src/linda.cpp
        lib/src/tuple.cpp
        lib/src/file_manager.cpp
        lib/src/parser.cpp)

add_executable(catch_tests_run
        tests/FileManagerTest.cpp
        lib/src/file_manager.cpp)