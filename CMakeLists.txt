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

Include(FetchContent)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git GIT_TAG origin/devel)
        FetchContent_GetProperties(Catch2)
        if(NOT catch2_POPULATED)
            FetchContent_Populate(Catch2)
            add_subdirectory("${catch2_SOURCE_DIR}"
    "${catch2_BINARY_DIR}")
        endif()

add_executable(CatchTests tests/FileManagerTest.cpp lib/src/file_manager.cpp)
target_link_libraries(CatchTests Catch2::Catch2WithMain)
