cmake_minimum_required(VERSION 3.12)

project(MVector)

# https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#add_library(mvector STATIC MVector.cpp)

add_executable(mvector MVector.cpp)