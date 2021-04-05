#pragma once

#include "../container/binary-search-tree.h"

#include <algorithm>
#include <iterator>
#include <cassert>
#include <set>

// bubble_sort
// selection_sort
// insertion_sort
// quick_sort
// merge_sort
// heap_sort
// unbalanced_tree_sort
// balanced_tree_sort

namespace sort {
    // Bubble Sort
    // Time complexity : Worst n^2, Average n^2, Best n
    // Space complexity : 1
    // Stable : Yes
    template< class IterT >
    inline void bubble_sort(IterT first, IterT last) {
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

    // Selection Sort
    // Time complexity: Worst n^2,  Average n^2, Best n^2
    // Space complexity: 1
    // Stable: No
    template< class IterT >
    inline void selection_sort(IterT first, IterT last) {
        for (auto iter = first; iter != last; ++iter) {
            std::iter_swap(iter, std::min_element(iter, last));
        }
    }

    template< class IterT >
    inline void selection_sort_2(IterT first, IterT last) {
        // for [first, last-1)
        for (IterT iter = first; iter != std::prev(last); ++iter) {
            // find min element [iter + 1, last)
            const IterT iter_min = std::min_element(std::next(iter), last);
            if (*iter_min < *iter)
                std::iter_swap(iter, iter_min);
        }
    }

    // The same as selection_sort2() but std::min_element replaced by self-implemented find min element loop
    // DO NOT USE THIS FUNCTION. Slow implemenation. It's used for benchmark only.
    template< class IterT >
    inline void selection_sort_3(IterT first, IterT last) {
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

    // Insertion Sort
    // Time complexity: Worst  n^2, Average n^2, Best n
    // Space complexity : 1
    // Stable : Yes
    template <typename IterT>
    inline void insertion_sort(IterT first, IterT last) {
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

    // Quick Sort

    template< class IterT >
    inline void quick_sort(IterT first, IterT last) {
        if (first == last)
            return;

        // Partitioning. Hoare partition scheme
        const auto pivot = *(first + (std::distance(first, last) / 2));
        auto bound1 = std::partition(first, last, [&pivot](const auto& i) { return i < pivot; });
        auto bound2 = std::partition(bound1, last, [&pivot](const auto& i) { return (i == pivot); });

        quick_sort(first, bound1);
        quick_sort(bound2, last);
    }

    // DO NOT USE THIS FUNCTION. Slow implemenation. It's used for benchmark only.
    template< class IterT >
    inline void quick_sort_2(IterT first, IterT last) {
        if (first == last)
            return;

        const auto pivot = *(first + (std::distance(first, last) / 2));

        // Partitioning. Hoare partition scheme
        auto left = first;
        auto right = last - 1;
        while (left < right) {
            while (*left < pivot) left++;
            while (*right > pivot) right--;
            if (left < right) {
                std::iter_swap(left, right);
                left++;
                right--;
            }
        }

        quick_sort_2(first, left);
        quick_sort_2(right, last);
    }

    // ! Stack overflow on a SORTED large array ~ 4000 elements. Replaced by Hoare partition scheme
    // DO NOT USE THIS FUNCTION. Can cause stack overflow. It's used for benchmark only.
    template< class IterT >
    void quick_sort_3(IterT first, IterT last) {
        if (first == last)
            return;
    
        // Partitioning. Lomuto’s partition scheme
        const auto pivot = (last - 1); // pivot element is a last element
        auto bound = std::partition(first, last, [&pivot](const auto& i) { return i < *pivot; });
        std::iter_swap(bound, pivot);
    
        quick_sort_3(first, bound);
        quick_sort_3(bound + 1, last);
    }

    // ! Stack overflow on a SORTED large array ~ 4000 elements. Replaced by Hoare partition scheme
    // DO NOT USE THIS FUNCTION. Slow implemenation and can cause stack overflow. It's used for benchmark only.
    template< class IterT >
    void quick_sort_4(IterT first, IterT last) {
        if (first == last)
            return;
    
        // Partitioning. Lomuto’s partition scheme
        const auto pivot = (last - 1); // pivot element is a last element
        auto bound = first;
        // for [first, last)
        for (auto iter = first; iter != last; ++iter) {
            if (*iter < *pivot) {
                std::iter_swap(bound, iter);
                ++bound;
            }
        }
        std::iter_swap(bound, pivot);
    
        quick_sort_4(first, bound);
        quick_sort_4(bound + 1, last);
    }

    // Merge Sort

    template< class IterT >
    inline void merge_sort(IterT first, IterT last) {
        if (first == last - 1)
            return;

        auto middle = first + (std::distance(first, last) / 2);
        merge_sort(first, middle);
        merge_sort(middle, last);
        std::inplace_merge(first, middle, last);
    }

    // Heap Sort

    template< class IterT >
    inline void heap_sort(IterT first, IterT last) {
        std::make_heap(first, last);
        std::sort_heap(first, last);
    }

    // Tree Sort

    template< class IterT >
    inline void unbalanced_tree_sort(IterT first, IterT last) {
        container::binary_search_tree<IterT::value_type> bst;

        // We need this pivot element to improve perfomance of sorted/reverse sorted array
        const auto pivot = (first + (std::distance(first, last) / 2));
        std::iter_swap(first, pivot);

        // for [first, last)
        for (auto iter = first; iter != last; ++iter) {
            bst.insert(*iter);
        }

        auto iter = first;
        bst.for_each<container::order_type::sort_order>([&iter](const auto& key) { *iter++ = key; });
        assert(iter == last);
        bst.clear();
    }

    template< class IterT >
    inline void balanced_tree_sort(IterT first, IterT last) {
        // multiset implemenation is red-black (balanced) binary search tree
        std::multiset<IterT::value_type> multi_set;

        // for [first, last)
        for (auto iter = first; iter != last; ++iter) {
            multi_set.insert(*iter);
        }

        auto i = first;
        for (auto iter = std::begin(multi_set); iter != std::end(multi_set); *i++ = *iter++);
        assert(i == last);
    }
}

