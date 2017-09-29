cmake_minimum_required(VERSION 3.8)
project(JosephRing)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp JosephRing.cpp JosephRing.h)
add_executable(JosephRing ${SOURCE_FILES})