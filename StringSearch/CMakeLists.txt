cmake_minimum_required(VERSION 3.6)
project(StringSearch)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    BaseSearch.cpp
    BaseSearch.h
    BM.cpp
    BM.h
    KMP.cpp
    KMP.h
    main.cpp)

add_executable(StringSearch ${SOURCE_FILES})