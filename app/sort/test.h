#pragma once

#include "sort.h"
#include "sort-sandbox.h"
#include "../helper.h"

#include <iostream>
#include <list>
#include <array>
#include <random>
#include <vector>

namespace sort
{

    class test {
    private:
        using SORT_TYPE = int;
        using SORT_CONTAINER = std::vector<SORT_TYPE>;

        std::array<SORT_TYPE, 3000> _unsorted_test_array{ 0 };
        std::vector<SORT_TYPE> _sorted_test_array;

    public:
        test() = default;
        test(const test& other) = delete;
        test(test&& other) = delete;
        test& operator = (const test& other) = delete;
        ~test() = default;

        void run() {
            initialize();
            test_cases();
        }

    private:
        void initialize() {
            _sorted_test_array.clear();

            // Fill unsorted_test_array with random data
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<SORT_TYPE> dist(std::numeric_limits<SORT_TYPE>::min(), std::numeric_limits<SORT_TYPE>::max());
            //std::uniform_int_distribution<SORT_TYPE> dist(1, 10);
            for (auto i = begin(_unsorted_test_array); i != end(_unsorted_test_array); ++i) {
                *i = dist(rng);
            }

            // unsorted_test_array -> sorted_test_array 
            _sorted_test_array.assign(begin(_unsorted_test_array), end(_unsorted_test_array));
            std::sort(begin(_sorted_test_array), end(_sorted_test_array));
            //std::sort(begin(_unsorted_test_array), end(_unsorted_test_array));
        }

        void test_cases() const {
            using IterType = SORT_CONTAINER::iterator;

            std::vector<std::pair<std::string, std::function<void(IterType b, IterType e)>>> test_cases{
                {"std::sort", [](IterType b, IterType e) { std::sort(b, e); } },
                {"std::stable_sort", [](IterType b, IterType e) { std::stable_sort(b, e); } },
                {"bubble_sort", [](IterType b, IterType e) { sort::bubble_sort(b, e); }},
                {"odd_even_sort", [](IterType b, IterType e) { sort::odd_even_sort(b, e); }},
                {"cocktail_shaker_sort", [](IterType b, IterType e) { sort::cocktail_shaker_sort(b, e); }},
                {"cocktail_shaker_sort_2", [](IterType b, IterType e) { sort::sandbox::cocktail_shaker_sort_2(b, e); }},
                {"selection_sort", [](IterType b, IterType e) { sort::selection_sort(b, e); }},
                {"selection_sort_2", [](IterType b, IterType e) { sort::sandbox::selection_sort_2(b, e); }},
                {"selection_sort_3", [](IterType b, IterType e) { sort::sandbox::selection_sort_3(b, e); }},
                {"insertion_sort", [](IterType b, IterType e) { sort::insertion_sort(b, e); }},
                {"insertion_sort_2", [](IterType b, IterType e) { sort::sandbox::insertion_sort_2(b, e); }},
                {"quick_sort", [](IterType b, IterType e) { sort::quick_sort(b, e); }},
                {"quick_sort_2", [](IterType b, IterType e) { sort::sandbox::quick_sort_2(b, e); }},
                {"quick_sort_3", [](IterType b, IterType e) { sort::sandbox::quick_sort_3(b, e); }},
                {"quick_sort_4", [](IterType b, IterType e) { sort::sandbox::quick_sort_4(b, e); }},
                {"unbalanced_tree_sort", [](IterType b, IterType e) { sort::unbalanced_tree_sort(b, e); }},
                {"balanced_tree_sort", [](IterType b, IterType e) { sort::balanced_tree_sort(b, e); }},
                {"merge_sort", [](IterType b, IterType e) { sort::merge_sort(b, e); }},
                {"heap_sort", [](IterType b, IterType e) { sort::heap_sort(b, e); }},
            };

            for (auto f : test_cases) {
                std::cout << f.first << " : ";

                SORT_CONTAINER test_array(begin(_unsorted_test_array), end(_unsorted_test_array));
                auto t = helper::benchmark_call_ms([&]() {f.second(begin(test_array), end(test_array)); });

                std::cout << "Invocation time (ms): " << t << ", ";
                std::cout << "Elements number: " << test_array.size() << ", ";
                std::cout << (std::equal(begin(test_array), end(test_array), begin(_sorted_test_array)) ? "[OK]" : "[FAIL]") << std::endl;
            }
        }
    };
}

