cmake_minimum_required(VERSION 3.9)
project(FamilyTree)

set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_EXE_LINKER_FLAGS -static)

add_executable(FamilyTree
        FmailyTree.cpp
        FmailyTree.h
        Hint.h
        main.cpp
        TestFamilyTree.cpp
        TestFamilyTree.h)
