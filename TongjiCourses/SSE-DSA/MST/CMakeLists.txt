cmake_minimum_required(VERSION 3.8)
project(MST)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Graph.cpp Graph.h Mst/Prim.cpp Mst/Prim.h Mst/Mst.h Mst/Kruskal.cpp Mst/Kruskal.h Mst/Mst.cpp)
add_executable(MST ${SOURCE_FILES})