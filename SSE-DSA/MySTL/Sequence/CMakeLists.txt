cmake_minimum_required(VERSION 3.8)
project(Sequence)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES test.cpp Sequence.h MyArray.h MyVector.h MyQueue.h MyPriorityQueue.h Queue.h)
add_executable(Sequence ${SOURCE_FILES})