cmake_minimum_required(VERSION 3.8)
project(SortTree)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp BinaryTree/BaseTree.h BinaryTree/TreeNode.h)
add_executable(SortTree ${SOURCE_FILES})