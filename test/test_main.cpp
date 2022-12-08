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

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}