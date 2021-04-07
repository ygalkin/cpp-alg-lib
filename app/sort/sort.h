#pragma once

#include "../container/binary-search-tree.h"

#include <algorithm>
#include <cassert>
#include <set>

// bubble_sort
// odd_even_sort
// cocktail_shaker_sort
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
        if (first == last)
            return;

        // for [last, first)
        for (auto iter_a = last; iter_a != first; --iter_a) {
            auto is_swapped{ false };
            // for [first, iter_a - 1)
            for (auto iter_b = first; iter_b != std::prev(iter_a); ++iter_b) {
                // if *iter_b > *(iter_b + 1)
                if (*iter_b > *std::next(iter_b)) {
                    std::iter_swap(iter_b, std::next(iter_b));
                    is_swapped = true;
                }
            }

            if (!is_swapped)
                break;
        }
    }

    // Odd Even sort (Brick sort). It's extension of Bubble sort.

    template< class IterT >
    inline void odd_even_sort(IterT first, IterT last) {
        if (first == last)
            return;

        auto is_sorted{ false };
        const auto prev_last{ std::prev(last) };

        while (!is_sorted) {

            is_sorted = true;

            // for [first + 1, last - 1)
            for (auto iter = std::next(first); iter < prev_last; iter = std::next(iter, 2)) {
                const auto next_iter{ std::next(iter) };
                if (*iter > *next_iter) {
                    std::iter_swap(iter, next_iter);
                    is_sorted = false;
                }
            }

            // for [first, last - 1)
            for (auto iter = first; iter < prev_last; iter = std::next(iter, 2)) {
                const auto next_iter{ std::next(iter) };
                if (*iter > *next_iter) {
                    std::iter_swap(iter, next_iter);
                    is_sorted = false;
                }
            }
        }
    }

    // Cocktail shaker sort. It's extension of Bubble sort.

    template< class IterT >
    inline void cocktail_shaker_sort(IterT first, IterT last) {
        if (first == last)
            return;

        auto is_swapped{ false };
        auto prev_last{ std::prev(last) };
        auto next_first{ first };

        do {
            // forward pass
            is_swapped = false;

            // for [first, last - 1)
            for (auto iter = next_first; iter != prev_last; ++iter) {
                const auto next_iter{ std::next(iter) };
                if (*iter > *next_iter) {
                    std::iter_swap(iter, next_iter);
                    is_swapped = true;
                }
            }

            if (!is_swapped)
                break;
            --prev_last;

            // reverse pass

            // for [last - 1, first)
            for (auto iter = prev_last; iter != next_first; --iter) {
                const auto prev_iter{ std::prev(iter) };
                if (*iter < *prev_iter) {
                    std::iter_swap(iter, prev_iter);
                    is_swapped = true;
                }
            }
            ++next_first;
        } while (is_swapped);
    }

    // Selection Sort
    // Time complexity: Worst n^2,  Average n^2, Best n^2
    // Space complexity: 1
    // Stable: No
    template< class IterT >
    inline void selection_sort(IterT first, IterT last) {
        if (first == last)
            return;

        // for [first, last-1)
        const auto prev_last = std::prev(last);
        for (auto iter = first; iter != prev_last; ++iter) {
            // find min element [iter + 1, last)
            const auto iter_min = std::min_element(std::next(iter), last);
            if (*iter_min < *iter)
                std::iter_swap(iter, iter_min);
        }
    }

    // Insertion Sort
    // Time complexity: Worst  n^2, Average n^2, Best n
    // Space complexity : 1
    // Stable : Yes
    template <typename IterT>
    inline void insertion_sort(IterT first, IterT last) {
        if (first == last)
            return;

        // for [first + 1, last)
        for (auto iter = std::next(first); iter != last; ++iter) {
            auto val{ std::move(*iter) };
            auto iter_curr{ iter };
            for (auto iter_prev = std::prev(iter); *iter_prev > val; --iter_prev) {
                *iter_curr = std::move(*iter_prev);
                iter_curr = iter_prev;
                if (iter_prev == first)
                    break;
            }

            //if (*iter_curr != val)
            *iter_curr = std::move(val);
        }
    }

    // Quick Sort

    template< class IterT >
    inline void quick_sort(IterT first, IterT last) {
        if (first == last)
            return;

        // Partitioning. Hoare partition scheme
        const auto pivot = *std::next(first, (std::distance(first, last) / 2));
        auto bound1 = std::partition(first, last, [&pivot](const auto& i) { return i < pivot; });
        auto bound2 = std::partition(bound1, last, [&pivot](const auto& i) { return (i == pivot); });

        quick_sort(first, bound1);
        quick_sort(bound2, last);
    }

    // Merge Sort

    template< class IterT >
    inline void merge_sort(IterT first, IterT last) {
        if (first == last) // empty sequence to sort
            return;

        // if (first == last - 1)
        if (first == std::prev(last)) // just one element in a sequence
            return;

        auto middle = std::next(first, (std::distance(first, last) / 2));
        merge_sort(first, middle);
        merge_sort(middle, last);
        // merges two consecutive sorted ranges [first, middle) and [middle, last) into one sorted range [first, last).
        // this function attempts to allocate a temporary buffer. If the allocation fails, the less efficient algorithm is chosen.
        std::inplace_merge(first, middle, last);
    }

    // Heap Sort

    template< class IterT >
    inline void heap_sort(IterT first, IterT last) {
        if (first == last)
            return;

        std::make_heap(first, last);
        std::sort_heap(first, last);
    }

    // Tree Sort

    template< class IterT >
    inline void unbalanced_tree_sort(IterT first, IterT last) {
        if (first == last)
            return;

        container::binary_search_tree<IterT::value_type> bst;

        // We need this pivot element to improve perfomance of sorted/reverse sorted array
        const auto pivot = std::next(first, (std::distance(first, last) / 2));
        std::iter_swap(first, pivot);

        // for [first, last)
        for (auto iter = first; iter != last; ++iter)
            bst.insert(*iter);

        auto iter{ first };
        bst.for_each<container::order_type::sort_order>([&iter](const auto& key) { *iter++ = key; });
        assert(iter == last);
        bst.clear();
    }

    template< class IterT >
    inline void balanced_tree_sort(IterT first, IterT last) {
        if (first == last)
            return;

        // multiset implemenation is red-black (balanced) binary search tree
        std::multiset<IterT::value_type> balanced_bst;

        // for [first, last)
        for (auto iter = first; iter != last; ++iter)
            balanced_bst.insert(*iter);

        auto i{ first };
        for (const auto& key : balanced_bst)
            *i++ = key;

        assert(i == last);
    }
}

