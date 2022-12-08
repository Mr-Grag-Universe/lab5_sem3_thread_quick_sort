cmake_minimum_required(VERSION 3.16)
project(PROGECT)
set(CMAKE_CXX_STANDARD 20)

add_compile_options(
    -Werror

    -Wall
    -Wextra
    -Wpedantic

    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo

    -v
)

add_subdirectory(src)
add_subdirectory(test)

add_executable(main_test main.cpp)
target_include_directories(main_test PRIVATE src)
target_link_libraries(main_test my_alg)
target_link_libraries(sort_tests my_alg)