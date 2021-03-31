#pragma once

#include <algorithm>

namespace sort {

// Selection Sort
// Time complexity: Worst n^2,  Average n^2, Best n^2
// Space complexity: 1
// Method: Selection
// Stable: No
// Class: Comparison sort
    class selection_sort {
    public:
        selection_sort() = default;
        selection_sort(const selection_sort& other) = default;
        selection_sort(selection_sort&& other) = default;
        selection_sort& operator = (const selection_sort& other) = default;
        ~selection_sort() = default;

        template< class IterT >
        void sort(IterT first, IterT last) {
            for (IterT iter = first; iter != std::prev(last); ++iter) {
                IterT iter_min = std::min_element(std::next(iter), last);
                if (*iter_min < *iter) 
                    std::iter_swap(iter, iter_min);
            }
        }
    };
}

//    vector<int> sortArray(vector<int>& nums) {
//        for (auto iter = begin(nums); iter != end(nums); ++iter) {
//            iter_swap(iter, min_element(iter, end(nums)));
//        }
//        return nums;
//    }

//template< class T >
//void sort(T first, T last) {
//    for (T iter_a = first; iter_a != last - 1; ++iter_a) {
//        T min = iter_a;
//
//        for (T iter_b = iter_a + 1; iter_b != last; ++iter_b) {
//            if (*iter_b < *min) {
//                min = iter_b;
//            }
//        }
//
//        std::iter_swap(iter_a, min);
//    }
//}
