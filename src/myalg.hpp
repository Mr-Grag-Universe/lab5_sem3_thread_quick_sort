#ifndef TQ_SORT
#define TQ_SORT

#include <iostream>
#include <functional>
#include <iterator>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <future>

namespace my_alg {

    #include "myalg.hpp"

    /// @brief вспомогательная функция.
    /// @tparam IteratorType - тип передаваемого/возвращаемого итератора
    /// @param begin 
    /// @param end 
    /// @return выбирает и возвращает итератор на опорный элемент
    template<typename IteratorType>
    IteratorType select_ref_el(IteratorType begin, IteratorType end) {
        auto diff = std::distance(begin, end);
        return begin+diff/2;
    }

    /// @brief вспомогательная функция для quick-sort - аналог библиотечного
    /// @brief работает по алгоритму Хоара. Все элементы < опорного переносит налево, > - направо
    /// @tparam IteratorType 
    /// @param begin 
    /// @param end 
    /// @param comp 
    /// @return возвращает итератор на край равних опорному элементу элементов
    template<typename IteratorType>
    IteratorType partition(IteratorType begin, IteratorType end, std::function<bool (const typename std::iterator_traits<IteratorType>::value_type & em)> comp) {
        --end;
        while (true) {
            while (comp(*begin))
                ++begin;
            while (!comp(*end))
                --end;
            if (std::distance(begin, end) <= 0)
                return end;
            std::swap(*(begin++), *(end--));
        }
    }

    /// @brief рекурсивный вариант быстрой сортировки
    /// @brief опорным элементом выбирается медиана
    /// @tparam IteratorType - тип передаваемых итераторов
    /// @param begin - итератор на первый элемент
    /// @param end - указатель next(от последнего элемента)
    /// @return рекурсивно на месте сортирует массив за статистическое O(n*log(n))
    template<typename IteratorType>
    void quick_sort_recursive(IteratorType begin, IteratorType end) {
        // тип данных в итерируемой структуре данных
        using Type = typename std::iterator_traits<IteratorType>::value_type;

        // смотрим на длину массива. если надо бросаем исключение
        const auto len = std::distance(begin, end);
        if (len < 0)
            throw std::invalid_argument("begin-iterator is later than the end-iterator: len is \"0\"");

        if(begin == end) return;

        // выбираем опорный элемент
        auto ref_iter = select_ref_el(begin, end);
        Type pivot = *ref_iter;
        
        // сортируем относительно опорного элемента
        auto middle1 = std::partition(begin, end, [pivot](const auto& em) {
            return em < pivot;
        });
        auto middle2 = std::partition(begin, end, [pivot](const auto& em) {
            return !(pivot < em);
        });

        [[maybe_unused]] auto middle3 = std::partition(begin, end, [pivot](const auto& em) {
            return !(pivot < em);
        });
        [[maybe_unused]] auto middle4 = std::partition(begin, end, [pivot](const auto& em) {
            return em < pivot;
        });
        // std::cout << "m3 - m2: " << std::distance(middle3, middle2) << ";\n";
        // std::cout << "m4 - m1: " << std::distance(middle4, middle1) << ";\n";

        // продолжаем рекурсию на неотсортированные концы
        quick_sort_recursive(begin, middle1);
        quick_sort_recursive(middle2, end);
    }

    template <typename Type>
    void quick_sort_vector(std::vector <Type> & v) {
        quick_sort_recursive(v.begin(), v.end());
    }

    using MyRNG = std::mt19937_64;  // the Mersenne Twister with a popular choice of parameters
    MyRNG rng;                   // e.g. keep one global instance (per thread)
    
    template <typename Type>
    std::vector<Type> generate_vector(std::pair<Type, Type> frame, size_t n) {
        using namespace std::chrono;
        std::this_thread::sleep_for(1000ms);
        uint64_t ms = static_cast<uint64_t>(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
        uint64_t seed_val = ms;           // populate somehow
        std::vector<Type> v(n);

        rng.seed(seed_val);
        std::uniform_int_distribution<Type> dist(frame.first, frame.second);
        for (size_t i = 0; i < n; ++i) {
            v[i] = dist(rng);
        }

        return v;
    }

    template <typename IteratorType, typename StreamType>
    void iter_print(IteratorType first, IteratorType last, StreamType & stream) {
        auto dist = std::distance(first, last);
        if (dist < 0)
            throw std::invalid_argument("begin-iterator is later than the end-iterator");
        while (first != last) {
            stream << *first << " ";
            ++first;
        }
        stream << std::endl;
    }

    template<typename IteratorType>
    void quick_thread_sort(IteratorType begin, IteratorType end) {
        // тип данных в итерируемой структуре данных
        using Type = typename std::iterator_traits<IteratorType>::value_type;

        // смотрим на длину массива. если надо бросаем исключение
        const auto len = std::distance(begin, end);
        if (len < 0)
            throw std::invalid_argument("begin-iterator is later than the end-iterator: len is \"0\"");

        if(begin == end) return;

        // выбираем опорный элемент
        auto ref_iter = select_ref_el(begin, end);
        Type pivot = *ref_iter;
        
        // сортируем относительно опорного элемента
        auto middle1 = std::partition(begin, end, [pivot](const auto& em) {
            return em < pivot;
        });
        auto middle2 = std::partition(begin, end, [pivot](const auto& em) {
            return !(pivot < em);
        });

        // продолжаем рекурсию на неотсортированные концы
        auto left = std::async(std::launch::async, [&]() {
            return quick_thread_sort(begin, middle1);
        });
        quick_thread_sort(middle2, end);
    }
};

#endif