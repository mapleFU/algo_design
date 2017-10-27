cmake_minimum_required(VERSION 3.8)
project(FamilyTree)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp FmailyTree.cpp FmailyTree.h TestFamilyTree.cpp TestFamilyTree.h)
add_executable(FamilyTree ${SOURCE_FILES})