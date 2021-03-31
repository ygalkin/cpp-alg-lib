#pragma once

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
        }

    private:
        static void test_bubble_sort() {
            std::cout << "-- Bubble Sort ---" << std::endl;
            std::list<int> arr{ 10, 4, 0, -1,  std::numeric_limits<int>::min(), -2, 33, std::numeric_limits<int>::max(), 11 };

            helper::out_each(std::cout, arr) << std::endl;
            bubble_sort().sort(begin(arr), end(arr));
            helper::out_each(std::cout, arr) << std::endl;
        }

        static void test_selection_sort() {
            std::cout << "-- Selection Sort ---" << std::endl;
            std::array<int, 9> arr{ {10, 4, 0, -1,  std::numeric_limits<int>::min(), -2, 33, std::numeric_limits<int>::max(), 11 } };
            helper::out_each(std::cout, arr) << std::endl;

            {
                std::list<int> arr1(begin(arr), end(arr));
                selection_sort().sort(begin(arr1), end(arr1));
                helper::out_each(std::cout, arr1) << std::endl;
            }

            {
                std::list<int> arr2(begin(arr), end(arr));
                selection_sort().sort(begin(arr2), end(arr2));
                helper::out_each(std::cout, arr2) << std::endl;
            }
        }

        static void test_insertion_sort() {
            std::cout << "-- Insertion Sort ---" << std::endl;
            std::list<int> arr{ 10, 4, 0, -1,  std::numeric_limits<int>::min(), -2, 33, std::numeric_limits<int>::max(), 11 };

            helper::out_each(std::cout, arr) << std::endl;
            insertion_sort().sort(begin(arr), end(arr));
            helper::out_each(std::cout, arr) << std::endl;
        }
    };

}
