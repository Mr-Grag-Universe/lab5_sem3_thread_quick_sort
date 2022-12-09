#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include "myalg.hpp"

bool my_comp(int a, int b) { return a < b; }

TEST(simple, quick_recurcive_sort)
{
    std::vector<int> v = my_alg::generate_vector(std::make_pair(0, 10), 10);
    my_alg::iter_print(v.begin(), v.end(), std::cout);
    my_alg::quick_sort_recursive(v.begin(), v.end());
    my_alg::iter_print(v.begin(), v.end(), std::cout);
}

TEST(million, quick_recurcive_sort)
{
    std::vector<int> v = my_alg::generate_vector(std::make_pair(-100, 100), 1'000'000);

    // засекаем время сортировки
    auto start_time = std::chrono::steady_clock::now();
    my_alg::quick_sort_vector(v);
    auto finish_time = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(finish_time-start_time) << std::endl;

    for (size_t i = 0, l = v.size()-1; i < l; ++i) {
        if (v[i] > v[i+1]) {
            std::cout << "неверно отсортировано\n";
        }
    }
}

TEST(simple, quick_thread_sort)
{
    std::vector<int> v = my_alg::generate_vector(std::make_pair(0, 10), 10);
    my_alg::iter_print(v.begin(), v.end(), std::cout);
    my_alg::quick_thread_sort<std::vector<int>::iterator, 4>(v.begin(), v.end());
    my_alg::iter_print(v.begin(), v.end(), std::cout);
}

TEST(million, quick_thread_sort)
{
    std::vector<int> v = my_alg::generate_vector(std::make_pair(-100, 100), 1'000'000);

    // засекаем время сортировки
    auto start_time = std::chrono::steady_clock::now();
    my_alg::quick_thread_sort<std::vector<int>::iterator, 4>(v.begin(), v.end());
    auto finish_time = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(finish_time-start_time) << std::endl;

    for (size_t i = 0, l = v.size()-1; i < l; ++i) {
        if (v[i] > v[i+1]) {
            std::cout << "неверно отсортировано\n";
        }
    }
}

TEST(million, compare) {
    std::chrono::duration simple_d = std::chrono::steady_clock::now()-std::chrono::steady_clock::now();
    std::chrono::duration thread_d = std::chrono::steady_clock::now()-std::chrono::steady_clock::now();
    for (size_t i = 0; i < 10; ++i) {
        std::vector<int> v1 = my_alg::generate_vector(std::make_pair(-100, 100), 1'000'000);
        std::vector<int> v2 = v1;

        // засекаем время сортировки
        auto start_time = std::chrono::steady_clock::now();
        my_alg::quick_sort_recursive(v1.begin(), v1.end());
        auto finish_time = std::chrono::steady_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(finish_time-start_time) << std::endl;
        simple_d += finish_time-start_time;

        // засекаем время сортировки
        start_time = std::chrono::steady_clock::now();
        my_alg::quick_thread_sort<std::vector<int>::iterator, 1>(v2.begin(), v2.end());
        finish_time = std::chrono::steady_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(finish_time-start_time) << std::endl;
        thread_d += finish_time-start_time;
    }

    std::cout << "average time: " << simple_d/10 << " and " << thread_d/10 << std::endl;
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}