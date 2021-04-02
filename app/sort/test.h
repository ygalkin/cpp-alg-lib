#pragma once

#include "tree-sort.h"
#include "quick-sort.h"
#include "selection-sort.h"
#include "insertion-sort.h"
#include "bubble-sort.h"
#include "../helper.h"

#include<iostream>
#include<list>
#include<array>
#include<random>
#include<vector>

namespace sort {
    class test {
    private:
        using SORT_TYPE = int;
        using SORT_CONTAINER = std::vector<SORT_TYPE>;

        std::array<SORT_TYPE, 2000> _unsorted_test_array{0};
        std::vector<SORT_TYPE> _sorted_test_array;

    public:
        test() = default;
        test(const test& other) = delete;
        test(test&& other) = delete;
        test& operator = (const test& other) = delete;
        ~test() = default;

        void run() {
            _sorted_test_array.clear();

            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<SORT_TYPE> dist(std::numeric_limits<SORT_TYPE>::min(), std::numeric_limits<SORT_TYPE>::max());
            for (auto i = 0; i < _unsorted_test_array.size(); ++i) {
                _unsorted_test_array[i] = dist(rng);
            }
            _sorted_test_array.assign(begin(_unsorted_test_array), end(_unsorted_test_array));
            std::sort(begin(_sorted_test_array), end(_sorted_test_array));

            test_bubble_sort();
            test_selection_sort();
            test_insertion_sort();
            test_quick_sort();
            test_tree_sort();
        }

    private:

        void test_bubble_sort() {
            std::cout << "=== Bubble Sort ===" << std::endl;
            {
                SORT_CONTAINER test_array(begin(_unsorted_test_array), end(_unsorted_test_array));

                auto t = helper::benchmark_call_ms([&test_array]() { bubble_sort().sort(begin(test_array), end(test_array)); });

                std::cout << "Elements number: " << test_array.size() << std::endl;
                std::cout << "Invocation time (ms): " << t << std::endl;
                std::cout << (std::equal(begin(test_array), end(test_array), begin(_sorted_test_array)) ? "[OK]" : "FAIL") << std::endl; 
            }
        }

        void test_selection_sort() {
            std::cout << "=== Selection Sort ===" << std::endl;
            {
                SORT_CONTAINER test_array(begin(_unsorted_test_array), end(_unsorted_test_array));

                auto t = helper::benchmark_call_ms([&test_array]() { selection_sort().sort(begin(test_array), end(test_array)); });

                std::cout << "Elements number: " << test_array.size() << std::endl;
                std::cout << "Invocation time (ms): " << t << std::endl;
                std::cout << (std::equal(begin(test_array), end(test_array), begin(_sorted_test_array)) ? "[OK]" : "FAIL") << std::endl;
            }

            {
                SORT_CONTAINER test_array(begin(_unsorted_test_array), end(_unsorted_test_array));

                auto t = helper::benchmark_call_ms([&test_array]() { selection_sort().sort2(begin(test_array), end(test_array)); });

                std::cout << "Elements number: " << test_array.size() << std::endl;
                std::cout << "Invocation time (ms): " << t << std::endl;
                std::cout << (std::equal(begin(test_array), end(test_array), begin(_sorted_test_array)) ? "[OK]" : "FAIL") << std::endl;
            }

            {
                SORT_CONTAINER test_array(begin(_unsorted_test_array), end(_unsorted_test_array));

                auto t = helper::benchmark_call_ms([&test_array]() { selection_sort().sort3(begin(test_array), end(test_array)); });

                std::cout << "Elements number: " << test_array.size() << std::endl;
                std::cout << "Invocation time (ms): " << t << std::endl;
                std::cout << (std::equal(begin(test_array), end(test_array), begin(_sorted_test_array)) ? "[OK]" : "FAIL") << std::endl;
            }
        }

        void test_insertion_sort() {
            std::cout << "=== Insertion Sort ===" << std::endl;
            {
                SORT_CONTAINER test_array(begin(_unsorted_test_array), end(_unsorted_test_array));

                auto t = helper::benchmark_call_ms([&test_array]() { insertion_sort().sort(begin(test_array), end(test_array)); });

                std::cout << "Elements number: " << test_array.size() << std::endl;
                std::cout << "Invocation time (ms): " << t << std::endl;
                std::cout << (std::equal(begin(test_array), end(test_array), begin(_sorted_test_array)) ? "[OK]" : "FAIL") << std::endl;
            }
        }

        void test_quick_sort() {
            std::cout << "=== Quick Sort ===" << std::endl;
            {
                SORT_CONTAINER test_array(begin(_unsorted_test_array), end(_unsorted_test_array));

                auto t = helper::benchmark_call_ms([&test_array]() { quick_sort().sort(begin(test_array), end(test_array)); });

                std::cout << "Elements number: " << test_array.size() << std::endl;
                std::cout << "Invocation time (ms): " << t << std::endl;
                std::cout << (std::equal(begin(test_array), end(test_array), begin(_sorted_test_array)) ? "[OK]" : "FAIL") << std::endl;
            }
        }

        void test_tree_sort() {
            std::cout << "=== Tree Sort ===" << std::endl;
            {
                SORT_CONTAINER test_array(begin(_unsorted_test_array), end(_unsorted_test_array));

                auto t = helper::benchmark_call_ms([&test_array]() { tree_sort().unbalanced_bst_sort(begin(test_array), end(test_array)); });

                std::cout << "Elements number: " << test_array.size() << std::endl;
                std::cout << "Invocation time (ms): " << t << std::endl;
                std::cout << (std::equal(begin(test_array), end(test_array), begin(_sorted_test_array)) ? "[OK]" : "FAIL") << std::endl;
            }
        }
    };
}
