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
            for (auto iter = first; iter != last; ++iter) {
                std::iter_swap(iter, std::min_element(iter, last));
            }
        }

        template< class IterT >
        void sort2(IterT first, IterT last) {
            // for [first, last-1)
            for (IterT iter = first; iter != std::prev(last); ++iter) {
                // find min element [iter + 1, last)
                const IterT iter_min = std::min_element(std::next(iter), last);
                if (*iter_min < *iter)
                    std::iter_swap(iter, iter_min);
            }
        }

        // The same as sort2() but std::min_element replaced by self-implemented find min element loop
        template< class IterT >
        void sort3(IterT first, IterT last) {
            // for [first, last-1)
            for (IterT iter_a = first; iter_a != std::prev(last); ++iter_a) {
                IterT iter_min = iter_a;
                // find min element [iter_a + 1, last)
                for (IterT iter_b = std::next(iter_a); iter_b != last; ++iter_b) {
                    if (*iter_b < *iter_min) {
                        iter_min = iter_b;
                    }
                }

                std::iter_swap(iter_a, iter_min);
            }
        }
    };
}
