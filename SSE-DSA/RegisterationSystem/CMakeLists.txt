cmake_minimum_required(VERSION 3.8)
project(DebugProject)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Student.cpp Student.h StudentList.cpp StudentList.h SystemView.cpp SystemView.h Command/BaseCommand.h Command/Commands.cpp Command/Commands.h Command/CommandManager.h)
add_executable(DebugProject ${SOURCE_FILES})