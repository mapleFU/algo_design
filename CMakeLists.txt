cmake_minimum_required(VERSION 3.6)
project(BinarySearchTree)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp BaseBinaryTree.cpp BaseBinaryTree.h BinarySearchTree.cpp BinarySearchTree.h avlTree.cpp avlTree.h splayTree.cpp splayTree.h)
add_executable(BinarySearchTree ${SOURCE_FILES})
