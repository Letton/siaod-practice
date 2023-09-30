cmake_minimum_required(VERSION 3.26)
project(2-practice)

set(CMAKE_CXX_STANDARD 23)

add_executable(main ./3-practice/main.cpp
        3-practice/HashTable.cpp
        3-practice/Book.cpp
        3-practice/Book.h
)