cmake_minimum_required(VERSION 3.8)
project(RegisterationSystem)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/Student.cpp src/Student.h src/SystemView.cpp src/SystemView.h src/StudentList.cpp src/StudentList.h src/StudentList.cpp src/StudentList.h src/Commands/BaseCommand.h src/Commands/Commands.cpp src/Commands/Commands.h src/Commands/CommandManager.cpp src/Commands/CommandManager.h)
add_executable(RegisterationSystem ${SOURCE_FILES})