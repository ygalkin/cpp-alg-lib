#pragma once

#include<iterator>

namespace sort {
// Insertion Sort
// Time complexity: Worst  n^2, Average n^2, Best n
// Space complexity : 1
// Method : Insertion
// Stable : Yes
// Class : Comparison sort
    class insertion_sort {
    public:
        insertion_sort() = default;
        insertion_sort(const insertion_sort& other) = default;
        insertion_sort(insertion_sort&& other) = default;
        insertion_sort& operator = (const insertion_sort& other) = default;
        ~insertion_sort() = default;

        template <typename IterT>
        void sort(IterT first, IterT last) {
            // for [first + 1, last)
            for (IterT iter = std::next(first); iter != last; ++iter) {
                auto iter_curr = iter;
                auto iter_prev = std::prev(iter);
                while (*iter_prev > *iter_curr) {
                    std::iter_swap(iter_prev, iter_curr);
                    if (iter_prev == first) {
                        break;
                    }
                    --iter_prev;
                    --iter_curr;
                }
            }
        }
    };
}