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

namespace sort {
    class test {
    public:
        test() = delete;
        test(const test& other) = delete;
        test(test&& other) = default;
        test& operator = (const test& other) = delete;
        ~test() = delete;

        static void run() {
            test_bubble_sort();
            test_selection_sort();
            test_insertion_sort();
            test_quick_sort();
            test_tree_sort();
        }

    private:
        static constexpr std::array<int, 10> _array_to_sort{ {10, 4, 0, -1,  std::numeric_limits<int>::min(), -2, -1, 33, std::numeric_limits<int>::max(), 11 } };

        static void test_bubble_sort() {
            std::cout << "-- Bubble Sort ---" << std::endl;
            std::list<int> arr(begin(_array_to_sort), end(_array_to_sort));

            helper::out_each(std::cout, arr) << std::endl;
            bubble_sort().sort(begin(arr), end(arr));
            helper::out_each(std::cout, arr) << std::endl;
        }

        static void test_selection_sort() {
            std::cout << "-- Selection Sort ---" << std::endl;
            helper::out_each(std::cout, _array_to_sort) << std::endl;

            {
                std::list<int> arr(begin(_array_to_sort), end(_array_to_sort));
                selection_sort().sort(begin(arr), end(arr));
                helper::out_each(std::cout, arr) << std::endl;
            }

            {
                std::list<int> arr(begin(_array_to_sort), end(_array_to_sort));
                selection_sort().sort2(begin(arr), end(arr));
                helper::out_each(std::cout, arr) << std::endl;
            }
        }

        static void test_insertion_sort() {
            std::cout << "-- Insertion Sort ---" << std::endl;
            std::list<int> arr(begin(_array_to_sort), end(_array_to_sort));
            
            helper::out_each(std::cout, arr) << std::endl;
            insertion_sort().sort(begin(arr), end(arr));
            helper::out_each(std::cout, arr) << std::endl;
        }

        static void test_quick_sort() {
            std::cout << "-- Quick Sort ---" << std::endl;
            std::list<int> arr(begin(_array_to_sort), end(_array_to_sort));

            helper::out_each(std::cout, arr) << std::endl;
            quick_sort().sort(begin(arr), end(arr));
            helper::out_each(std::cout, arr) << std::endl;
        }

        static void test_tree_sort() {
            std::cout << "-- Tree Sort ---" << std::endl;
            std::list<int> arr(begin(_array_to_sort), end(_array_to_sort));

            helper::out_each(std::cout, arr) << std::endl;
            tree_sort().unbalanced_tree_sort(begin(arr), end(arr));
            helper::out_each(std::cout, arr) << std::endl;
        }
    };

}
