cmake_minimum_required(VERSION 3.16)
project(my_alg)
set(CMAKE_CXX_STANDARD 20)

set(SOURCES
    sort.cpp
    quick_sort.cpp
)

add_library(my_alg ${SOURCES})