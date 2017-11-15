cmake_minimum_required(VERSION 3.8)
project(NQueens)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp NQueen.cpp NQueen.h)
add_executable(NQueens ${SOURCE_FILES})