# cmake_minimum_required(VERSION <specify CMake version here>)
project(main)

set(CMAKE_CXX_STANDARD 14)

add_executable(writelock src/writelock.cpp)
add_executable(readlock src/readlock.cpp)
