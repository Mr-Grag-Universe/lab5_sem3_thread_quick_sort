cmake_minimum_required(VERSION 3.16)
project(thread_quick_sort)
set(CMAKE_CXX_STANDARD 20)

set(SOURCES
    sort.cpp
)

add_library(${PROGECT_NAME} STATIC ${SOURCES})