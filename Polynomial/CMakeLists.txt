cmake_minimum_required(VERSION 3.6)
project(Polyno)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp poly.cpp poly.h)
add_executable(Polyno ${SOURCE_FILES})