cmake_minimum_required(VERSION 3.8)
project(Maze)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Maze.cpp Maze.h MyQueue.h)
add_executable(Maze ${SOURCE_FILES})