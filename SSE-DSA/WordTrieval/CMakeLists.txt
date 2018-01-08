cmake_minimum_required(VERSION 3.8)
project(WordTrieval)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp WordRecords/WordRecords.cpp WordRecords/WordRecords.h WordRecords/Record.cpp WordRecords/Record.h WordRecords/WordTokenizer.cpp WordRecords/WordTokenizer.h Tests/ReadTest.cpp Tests/ReadTest.h Tests/SearchTest.cpp Tests/SearchTest.h)
add_executable(WordTrieval ${SOURCE_FILES})