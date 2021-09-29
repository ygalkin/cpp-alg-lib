#ifndef _SORT_TEST_
#define _SORT_TEST_

#include "sort.h"
#include "sort-sandbox.h"
#include "helper.h"

#include <iostream>
#include <array>
#include <random>
#include <vector>
#include <unordered_set>
#include <string_view>

namespace sort {

    using SORT_TYPE = int;
    using SORT_CONTAINER = std::vector<SORT_TYPE>;
    using IterType = SORT_CONTAINER::iterator;

    inline constexpr auto ARRAY_SIZE = 100;
    inline const std::vector<std::pair<std::string_view, std::function<void(IterType b, IterType e)>>> _sort_algorithms{
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
    std::array<SORT_TYPE, ARRAY_SIZE> _unsorted_test_array{ 0 };
    std::vector<SORT_TYPE> _sorted_test_array;

    void print_footer(int64_t ms, size_t size) {
        std::cout << "time (ms): " << ms << ", " << "array size: " << size << std::endl;
    }

    void initialize() {
        _sorted_test_array.clear();

        // Fill unsorted_test_array with random data
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<SORT_TYPE> dist(std::numeric_limits<SORT_TYPE>::min(), std::numeric_limits<SORT_TYPE>::max());
        for (auto i = std::begin(_unsorted_test_array); i != std::end(_unsorted_test_array); ++i) {
            *i = dist(rng);
        }

        // unsorted_test_array -> sorted_test_array 
        _sorted_test_array.assign(std::cbegin(_unsorted_test_array), std::cend(_unsorted_test_array));
        std::sort(std::begin(_sorted_test_array), std::end(_sorted_test_array));
    }

    TEST_CASE("sort random array", "[sort]") {

        constexpr auto BENCHMARK_NAME = "Benchmark: random array";
        constexpr std::array<std::string_view, 1> test_case_skip_list{
            "quick_sort_2" // not implemented
        };

        initialize();

        std::cout << "**********[" << BENCHMARK_NAME << "]**********" << std::endl;

        for (const auto& f : _sort_algorithms) {
            std::cout << f.first << " : ";
            if (std::find(std::cbegin(test_case_skip_list), std::cend(test_case_skip_list), f.first) != std::cend(test_case_skip_list)) {
                std::cout << "[SKIPPED]" << std::endl;
                continue;
            }

            SORT_CONTAINER test_array(std::cbegin(_unsorted_test_array), std::cend(_unsorted_test_array));

            const auto t = helper::benchmark_call_ms([&]() {f.second(std::begin(test_array), std::end(test_array)); });

            print_footer(t, test_array.size());
            REQUIRE(std::equal(std::cbegin(test_array), std::cend(test_array), std::cbegin(_sorted_test_array)));
        }
    }

    TEST_CASE("sort sorted array", "[sort]") {
        constexpr auto BENCHMARK_NAME = "Benchmark: sorted array";
        constexpr std::array<std::string_view, 4> test_case_skip_list{
            "quick_sort_2", // not implemented
            "quick_sort_3",
            "quick_sort_4",
            "unbalanced_tree_sort"
        };

        initialize();

        std::cout << "**********[" << BENCHMARK_NAME << "]**********" << std::endl;

        for (const auto& f : _sort_algorithms) {
            std::cout << f.first << " : ";
            if (std::find(std::cbegin(test_case_skip_list), std::cend(test_case_skip_list), f.first) != std::cend(test_case_skip_list)) {
                std::cout << "[SKIPPED]" << std::endl;
                continue;
            }

            SORT_CONTAINER test_array(std::cbegin(_sorted_test_array), std::cend(_sorted_test_array));

            const auto t = helper::benchmark_call_ms([&]() {f.second(std::begin(test_array), std::end(test_array)); });

            print_footer(t, test_array.size());
            REQUIRE(std::equal(std::cbegin(test_array), std::cend(test_array), std::cbegin(_sorted_test_array)));
        }
    }

    TEST_CASE("sort empty array", "[sort]") {
        constexpr auto BENCHMARK_NAME = "Benchmark: empty array";
        constexpr std::array<std::string_view, 0> test_case_skip_list{};

        std::cout << "**********[" << BENCHMARK_NAME << "]**********" << std::endl;

        for (const auto& f : _sort_algorithms) {
            std::cout << f.first << " : ";
            if (std::find(std::cbegin(test_case_skip_list), std::cend(test_case_skip_list), f.first) != std::cend(test_case_skip_list)) {
                std::cout << "[SKIPPED]" << std::endl;
                continue;
            }

            SORT_CONTAINER test_array;

            const auto t = helper::benchmark_call_ms([&]() {f.second(std::begin(test_array), std::end(test_array)); });

            print_footer(t, test_array.size());
            REQUIRE(test_array.empty());
        }
    }

    TEST_CASE("sort 1 element array", "[sort]") {
        constexpr auto BENCHMARK_NAME = "Benchmark: one element array";
        constexpr std::array<std::string_view, 1> test_case_skip_list{ "cocktail_shaker_sort" };

        std::cout << "**********[" << BENCHMARK_NAME << "]**********" << std::endl;

        for (const auto& f : _sort_algorithms) {
            std::cout << f.first << " : ";
            if (std::find(std::cbegin(test_case_skip_list), std::cend(test_case_skip_list), f.first) != std::cend(test_case_skip_list)) {
                std::cout << "[SKIPPED]" << std::endl;
                continue;
            }
            constexpr auto ELEMENT_TO_SORT{ 42 };
            SORT_CONTAINER test_array{ ELEMENT_TO_SORT };

            const auto t = helper::benchmark_call_ms([&]() {f.second(std::begin(test_array), std::end(test_array)); });

            print_footer(t, test_array.size());
            REQUIRE(test_array[0] == ELEMENT_TO_SORT);
        }
    }
}

#endif