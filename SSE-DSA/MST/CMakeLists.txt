cmake_minimum_required(VERSION 3.8)
project(MST)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Graph.cpp Graph.h Prim.cpp Prim.h)
add_executable(MST ${SOURCE_FILES})