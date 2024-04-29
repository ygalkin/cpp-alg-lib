#ifndef _SORT_TEST_
#define _SORT_TEST_

#include "sort.h"
#include "sort-sandbox.h"
#include "detail.h"

#include <iostream>
#include <array>
#include <random>
#include <vector>
#include <unordered_set>
#include <string_view>

namespace sort {
    inline constexpr auto ARRAY_SIZE{ 100000 };

    using sort_type = int;
    using sort_container_helper = std::array<sort_type, ARRAY_SIZE>;
    using sort_container = std::vector<sort_type>;
    using IterType = sort_container::iterator;
    template <size_t size>
    using skip_list = std::array<std::string_view, size>;

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

    inline void print_footer(int64_t ms, size_t size) {
        std::cout << "time (ms): " << ms << ", " << "array size: " << size << std::endl;
    }

    inline void initialize(sort_container_helper& unsorted_test_array, sort_container_helper& sorted_test_array) {
        // Fill unsorted_test_array with random data
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<sort_type> dist(std::numeric_limits<sort_type>::min(), std::numeric_limits<sort_type>::max());
        for (auto i = std::begin(unsorted_test_array); i != std::end(unsorted_test_array); ++i) {
            *i = dist(rng);
        }

        // copy unsorted_test_array -> sorted_test_array 
        std::copy(std::cbegin(unsorted_test_array), std::cend(unsorted_test_array), std::begin(sorted_test_array));
        // sort sorted_test_array 
        std::sort(std::begin(sorted_test_array), std::end(sorted_test_array));
    }

    TEST_CASE("sort random array", "[sort]") {

        static constexpr auto BENCHMARK_NAME = "Benchmark: random array";
        static constexpr skip_list<1> SKIP_LIST{
            "quick_sort_2" // not implemented
        };

        sort_container_helper unsorted_test_array;
        sort_container_helper sorted_test_array;
        initialize(unsorted_test_array, sorted_test_array);

        std::cout << "**********[" << BENCHMARK_NAME << "]**********" << std::endl;

        for (const auto& f : _sort_algorithms) {

            const auto [name, sort_func] = f;

            std::cout << name << " : ";

            if (std::any_of(std::cbegin(SKIP_LIST), std::cend(SKIP_LIST), [&name](const auto& i) { return i == name; })) {
                std::cout << "[SKIPPED]" << std::endl;
                continue;
            }

            sort_container test_array(std::cbegin(unsorted_test_array), std::cend(unsorted_test_array));

            const auto t = detail::benchmark_call_ms([&]() {sort_func(std::begin(test_array), std::end(test_array)); });

            print_footer(t, test_array.size());
            REQUIRE(std::equal(std::cbegin(test_array), std::cend(test_array), std::cbegin(sorted_test_array)));
        }
    }

    TEST_CASE("sort sorted array", "[sort]") {
        static constexpr auto BENCHMARK_NAME = "Benchmark: sorted array";
        static constexpr skip_list<4> SKIP_LIST{
            "quick_sort_2", // not implemented
            "quick_sort_3",
            "quick_sort_4",
            "unbalanced_tree_sort"
        };

        sort_container_helper unsorted_test_array;
        sort_container_helper sorted_test_array;
        initialize(unsorted_test_array, sorted_test_array);

        std::cout << "**********[" << BENCHMARK_NAME << "]**********" << std::endl;

        for (const auto& f : _sort_algorithms) {

            const auto [name, sort_func] = f;

            std::cout << name << " : ";
            if (std::any_of(std::cbegin(SKIP_LIST), std::cend(SKIP_LIST), [&name](const auto& i) { return i == name; })) {
                std::cout << "[SKIPPED]" << std::endl;
                continue;
            }

            sort_container test_array(std::cbegin(sorted_test_array), std::cend(sorted_test_array));

            const auto t = detail::benchmark_call_ms([&]() {sort_func(std::begin(test_array), std::end(test_array)); });

            print_footer(t, test_array.size());
            REQUIRE(std::equal(std::cbegin(test_array), std::cend(test_array), std::cbegin(sorted_test_array)));
        }
    }

    TEST_CASE("sort empty array", "[sort]") {
        static constexpr auto BENCHMARK_NAME = "Benchmark: empty array";
        static constexpr skip_list<0> SKIP_LIST{};

        std::cout << "**********[" << BENCHMARK_NAME << "]**********" << std::endl;

        for (const auto& f : _sort_algorithms) {

            const auto [name, sort_func] = f;

            std::cout << name << " : ";
            if (std::any_of(std::cbegin(SKIP_LIST), std::cend(SKIP_LIST), [&name](const auto& i) { return i == name; })) {
                std::cout << "[SKIPPED]" << std::endl;
                continue;
            }

            sort_container test_array;

            const auto t = detail::benchmark_call_ms([&]() {sort_func(std::begin(test_array), std::end(test_array)); });

            print_footer(t, test_array.size());
            REQUIRE(test_array.empty());
        }
    }

    TEST_CASE("sort 1 element array", "[sort]") {
        static constexpr auto BENCHMARK_NAME = "Benchmark: one element array";
        static constexpr skip_list<1> SKIP_LIST{ "cocktail_shaker_sort" };

        std::cout << "**********[" << BENCHMARK_NAME << "]**********" << std::endl;

        for (const auto& f : _sort_algorithms) {

            const auto [name, sort_func] = f;

            std::cout << name << " : ";
            if (std::any_of(std::cbegin(SKIP_LIST), std::cend(SKIP_LIST), [&name](const auto& i) { return i == name; })) {
                std::cout << "[SKIPPED]" << std::endl;
                continue;
            }

            static constexpr auto ELEMENT_TO_SORT{ 42 };
            sort_container test_array{ ELEMENT_TO_SORT };

            const auto t = detail::benchmark_call_ms([&]() {sort_func(std::begin(test_array), std::end(test_array)); });

            print_footer(t, test_array.size());
            REQUIRE(test_array[0] == ELEMENT_TO_SORT);
        }
    }
}

#endif