#pragma once

#include "sort.h"
#include "sort-sandbox.h"
#include "../helper.h"

#include <iostream>
#include <list>
#include <array>
#include <random>
#include <vector>

class test {
private:
    using SORT_TYPE = int;
    using SORT_CONTAINER = std::vector<SORT_TYPE>;

    std::array<SORT_TYPE, 4001> _unsorted_test_array{ 0 };
    std::vector<SORT_TYPE> _sorted_test_array;

public:
    test() = default;
    test(const test& other) = delete;
    test(test&& other) = delete;
    test& operator = (const test& other) = delete;
    ~test() = default;

    void run() {
        initialize();
        test_odd_even_sort();
        test_selection_sort();
        test_insertion_sort();
        test_quick_sort();
        test_tree_sort();
        test_merge_sort();
        test_heap_sort();
        test_bubble_sort();
    }

private:
    void initialize() {
        _sorted_test_array.clear();

        // Fill unsorted_test_array with random data
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<SORT_TYPE> dist(std::numeric_limits<SORT_TYPE>::min(), std::numeric_limits<SORT_TYPE>::max());
        //std::uniform_int_distribution<SORT_TYPE> dist(1, 10);
        for (auto i = 0; i < _unsorted_test_array.size(); ++i) {
            _unsorted_test_array[i] = dist(rng);
        }

        // unsorted_test_array -> sorted_test_array 
        _sorted_test_array.assign(begin(_unsorted_test_array), end(_unsorted_test_array));
        std::sort(begin(_sorted_test_array), end(_sorted_test_array));
        //std::sort(begin(_unsorted_test_array), end(_unsorted_test_array));
    }

    void test_bubble_sort() const {
        std::cout << "=== Bubble Sort ===" << std::endl;
        {
            SORT_CONTAINER test_array(begin(_unsorted_test_array), end(_unsorted_test_array));

            auto t = helper::benchmark_call_ms([&test_array]() { sort::bubble_sort(begin(test_array), end(test_array)); });

            std::cout << "Elements number: " << test_array.size() << std::endl;
            std::cout << "Invocation time (ms): " << t << std::endl;
            std::cout << (std::equal(begin(test_array), end(test_array), begin(_sorted_test_array)) ? "[OK]" : "FAIL") << std::endl;
        }
    }

    void test_odd_even_sort() const {
        std::cout << "=== Odd Even Sort ===" << std::endl;
        {
            SORT_CONTAINER test_array(begin(_unsorted_test_array), end(_unsorted_test_array));

            auto t = helper::benchmark_call_ms([&test_array]() { sort::odd_even_sort(begin(test_array), end(test_array)); });

            std::cout << "Elements number: " << test_array.size() << std::endl;
            std::cout << "Invocation time (ms): " << t << std::endl;
            std::cout << (std::equal(begin(test_array), end(test_array), begin(_sorted_test_array)) ? "[OK]" : "FAIL") << std::endl;
        }
    }

    void test_selection_sort() const {
        std::cout << "=== Selection Sort ===" << std::endl;
        {
            SORT_CONTAINER test_array(begin(_unsorted_test_array), end(_unsorted_test_array));

            auto t = helper::benchmark_call_ms([&test_array]() { sort::selection_sort(begin(test_array), end(test_array)); });

            std::cout << "Elements number: " << test_array.size() << std::endl;
            std::cout << "Invocation time (ms): " << t << std::endl;
            std::cout << (std::equal(begin(test_array), end(test_array), begin(_sorted_test_array)) ? "[OK]" : "FAIL") << std::endl;
        }

        {
            SORT_CONTAINER test_array(begin(_unsorted_test_array), end(_unsorted_test_array));

            auto t = helper::benchmark_call_ms([&test_array]() { sort::sandbox::selection_sort_2(begin(test_array), end(test_array)); });

            std::cout << "Elements number: " << test_array.size() << std::endl;
            std::cout << "Invocation time (ms): " << t << std::endl;
            std::cout << (std::equal(begin(test_array), end(test_array), begin(_sorted_test_array)) ? "[OK]" : "FAIL") << std::endl;
        }

        {
            SORT_CONTAINER test_array(begin(_unsorted_test_array), end(_unsorted_test_array));

            auto t = helper::benchmark_call_ms([&test_array]() { sort::sandbox::selection_sort_3(begin(test_array), end(test_array)); });

            std::cout << "Elements number: " << test_array.size() << std::endl;
            std::cout << "Invocation time (ms): " << t << std::endl;
            std::cout << (std::equal(begin(test_array), end(test_array), begin(_sorted_test_array)) ? "[OK]" : "FAIL") << std::endl;
        }
    }

    void test_insertion_sort() const {
        std::cout << "=== Insertion Sort ===" << std::endl;
        {
            SORT_CONTAINER test_array(begin(_unsorted_test_array), end(_unsorted_test_array));

            auto t = helper::benchmark_call_ms([&test_array]() { sort::insertion_sort(begin(test_array), end(test_array)); });

            std::cout << "Elements number: " << test_array.size() << std::endl;
            std::cout << "Invocation time (ms): " << t << std::endl;
            std::cout << (std::equal(begin(test_array), end(test_array), begin(_sorted_test_array)) ? "[OK]" : "FAIL") << std::endl;

            //helper::out_each(std::cout, _unsorted_test_array) << std::endl;
            //helper::out_each(std::cout, test_array) << std::endl;
        }

        {
            SORT_CONTAINER test_array(begin(_unsorted_test_array), end(_unsorted_test_array));

            auto t = helper::benchmark_call_ms([&test_array]() { sort::sandbox::insertion_sort_2(begin(test_array), end(test_array)); });

            std::cout << "Elements number: " << test_array.size() << std::endl;
            std::cout << "Invocation time (ms): " << t << std::endl;
            std::cout << (std::equal(begin(test_array), end(test_array), begin(_sorted_test_array)) ? "[OK]" : "FAIL") << std::endl;
        }
    }

    void test_quick_sort() const {
        std::cout << "=== Quick Sort ===" << std::endl;
        {
            SORT_CONTAINER test_array(begin(_unsorted_test_array), end(_unsorted_test_array));

            auto t = helper::benchmark_call_ms([&test_array]() { sort::quick_sort(begin(test_array), end(test_array)); });

            std::cout << "Elements number: " << test_array.size() << std::endl;
            std::cout << "Invocation time (ms): " << t << std::endl;
            std::cout << (std::equal(begin(test_array), end(test_array), begin(_sorted_test_array)) ? "[OK]" : "FAIL") << std::endl;
        }

        //{
        //    SORT_CONTAINER test_array(begin(_unsorted_test_array), end(_unsorted_test_array));

        //    auto t = helper::benchmark_call_ms([&test_array]() { sort::quick_sort_2(begin(test_array), end(test_array)); });

        //    std::cout << "Elements number: " << test_array.size() << std::endl;
        //    std::cout << "Invocation time (ms): " << t << std::endl;
        //    std::cout << (std::equal(begin(test_array), end(test_array), begin(_sorted_test_array)) ? "[OK]" : "FAIL") << std::endl;
        //}
    }

    void test_tree_sort() const {
        std::cout << "=== Tree Sort ===" << std::endl;
        {
            SORT_CONTAINER test_array(begin(_unsorted_test_array), end(_unsorted_test_array));

            auto t = helper::benchmark_call_ms([&test_array]() { sort::unbalanced_tree_sort(begin(test_array), end(test_array)); });

            std::cout << "Elements number: " << test_array.size() << std::endl;
            std::cout << "Invocation time (ms): " << t << std::endl;
            std::cout << (std::equal(begin(test_array), end(test_array), begin(_sorted_test_array)) ? "[OK]" : "FAIL") << std::endl;
        }

        {
            SORT_CONTAINER test_array(begin(_unsorted_test_array), end(_unsorted_test_array));

            auto t = helper::benchmark_call_ms([&test_array]() { sort::balanced_tree_sort(begin(test_array), end(test_array)); });

            std::cout << "Elements number: " << test_array.size() << std::endl;
            std::cout << "Invocation time (ms): " << t << std::endl;
            std::cout << (std::equal(begin(test_array), end(test_array), begin(_sorted_test_array)) ? "[OK]" : "FAIL") << std::endl;
        }
    }

    void test_merge_sort() const {
        std::cout << "=== Merge Sort ===" << std::endl;
        {
            SORT_CONTAINER test_array(begin(_unsorted_test_array), end(_unsorted_test_array));

            auto t = helper::benchmark_call_ms([&test_array]() { sort::merge_sort(begin(test_array), end(test_array)); });

            std::cout << "Elements number: " << test_array.size() << std::endl;
            std::cout << "Invocation time (ms): " << t << std::endl;
            std::cout << (std::equal(begin(test_array), end(test_array), begin(_sorted_test_array)) ? "[OK]" : "FAIL") << std::endl;
        }
    }

    void test_heap_sort() const {
        std::cout << "=== Heap Sort ===" << std::endl;
        {
            SORT_CONTAINER test_array(begin(_unsorted_test_array), end(_unsorted_test_array));

            auto t = helper::benchmark_call_ms([&test_array]() { sort::heap_sort(begin(test_array), end(test_array)); });

            std::cout << "Elements number: " << test_array.size() << std::endl;
            std::cout << "Invocation time (ms): " << t << std::endl;
            std::cout << (std::equal(begin(test_array), end(test_array), begin(_sorted_test_array)) ? "[OK]" : "FAIL") << std::endl;
        }
    }
};

