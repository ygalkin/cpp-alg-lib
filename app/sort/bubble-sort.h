#pragma once

#include<iterator>

namespace sort {
    // Bubble Sort
    // Time complexity : Worst n^2, Average n^2, Best n
    // Space complexity : 1
    // Method : Exchanging
    // Stable : Yes
    // Class : Comparison sort
    class bubble_sort {
    public:
        bubble_sort() = default;
        bubble_sort(const bubble_sort& other) = default;
        bubble_sort(bubble_sort&& other) = default;
        bubble_sort& operator = (const bubble_sort& other) = default;
        ~bubble_sort() = default;

        template< class IterT >
        inline void sort(IterT first, IterT last) {
            // for [last, first)
            for (IterT iter_a = last; iter_a != first; --iter_a) {
                auto is_swapped{ false };
                // for [first, iter_a - 1)
                for (IterT iter_b = first; iter_b != std::prev(iter_a); ++iter_b) {
                    // if *iter_b > *(iter_b + 1)
                    if (*iter_b > *std::next(iter_b)) {
                        std::iter_swap(iter_b, std::next(iter_b));
                        is_swapped = true;
                    }
                }

                if (!is_swapped) { break; }
            }
        }
    };

}

//void sort(std::vector<int>& arr) {
//    const auto size{ arr.size() };

//    for (size_t i = 0; i < size - 1; ++i) {
//        auto is_swapped{ false };

//        for (size_t j = 0; j < size - 1 - i; ++j) {
//            if (arr[j] > arr[j + 1]) {
//                std::swap(arr[j], arr[j + 1]);
//                is_swapped = true;
//            }
//        }

//        if (!is_swapped) {
//            break;
//        }
//    }
//}
