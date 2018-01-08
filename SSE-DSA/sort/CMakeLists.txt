cmake_minimum_required(VERSION 3.6)
project(sort)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp sort.cpp sort.hpp tests.h)
add_executable(sort ${SOURCE_FILES})