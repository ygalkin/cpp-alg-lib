#ifndef _SORT_
#define _SORT_

#include "binary-search-tree.h"

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
        for (auto i = last; i != first; --i) {
            auto is_swapped{ false };
            // for [first, i - 1)
            const auto prev_i = std::prev(i);
            for (auto j = first; j != prev_i; ++j) {
                // if *j > *(j + 1)
                const auto next_j = std::next(j);
                if (*j > *next_j) {
                    std::iter_swap(j, next_j);
                    is_swapped = true;
                }
            }

            if (!is_swapped)
                break;
        }
    }

    // Odd Even sort (Brick sort). It's a variation of Bubble sort.
    template< class IterT >
    inline void odd_even_sort(IterT first, IterT last) {
        if (first == last)
            return;

        const auto begin{ std::next(first) };
        auto end{ std::prev(last) };
        for (auto is_sorted{ false }; !is_sorted;) {

            is_sorted = true;

            // for [first + 1, last - 1)
            for (auto i = begin; i < end; i = std::next(i, 2)) {
                const auto next_i{ std::next(i) };
                if (*i > *next_i) {
                    std::iter_swap(i, next_i);
                    is_sorted = false;
                }
            }

            // for [first, last - 1)
            for (auto i = first; i < end; i = std::next(i, 2)) {
                const auto next_i{ std::next(i) };
                if (*i > *next_i) {
                    std::iter_swap(i, next_i);
                    is_sorted = false;
                }
            }
        }
    }

    // Cocktail shaker sort. Bidirectional Bubble sort. It's a variation of Bubble sort.
    template< class IterT >
    inline void cocktail_shaker_sort(IterT first, IterT last) {
        if (first == last)
            return;

        auto is_swapped{ true };
        for (auto begin{ first }, end{ std::prev(last) }; is_swapped; ++begin, --end) {
            is_swapped = false;
            // one loop for forward and reverse pass
            for (auto i = begin, j = end; i != end; ++i, --j) {
                // forward pass
                const auto next_i{ std::next(i) };
                if (*i > *next_i) {
                    std::iter_swap(i, next_i);
                    is_swapped = true;
                }
                // reverse pass
                const auto prev_j{ std::prev(j) };
                if (*j < *prev_j) {
                    std::iter_swap(prev_j, j);
                    is_swapped = true;
                }
            }
        }
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
        const auto end = std::prev(last);
        for (auto i = first; i != end; ++i) {
            // find min element [i + 1, last)
            const auto min = std::min_element(std::next(i), last);
            if (*min < *i)
                std::iter_swap(i, min);
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
        for (auto i = std::next(first); i != last; ++i) {
            auto val{ std::move(*i) };
            auto hole{ i };
            for (auto j = std::prev(i); *j > val; --j) {
                *hole = std::move(*j);
                hole = j;
                if (j == first)
                    break;
            }

            //if (*hole != val)
            *hole = std::move(val);
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
    template< class IterT, class Compare>
    inline void heap_sort(IterT first, IterT last, Compare comp) {
        if (first == last)
            return;

        std::make_heap(first, last, comp);
        std::sort_heap(first, last, comp);
    }

    template< class IterT >
    inline void heap_sort(IterT first, IterT last) {
        heap_sort(first, last, std::less<>{});
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
        for (auto i = first; i != last; ++i)
            bst.insert(*i);

        auto j{ first };
        bst.for_each<container::order_type::sort_order>([&j](const auto& key) { *j++ = key; });
        assert(j == last);
        bst.clear();
    }

    template< class IterT >
    inline void balanced_tree_sort(IterT first, IterT last) {
        if (first == last)
            return;

        // multiset implemenation is red-black (balanced) binary search tree
        std::multiset<IterT::value_type> balanced_bst;

        // for [first, last)
        for (auto i = first; i != last; ++i)
            balanced_bst.insert(*i);

        auto j{ first };
        for (const auto& key : balanced_bst)
            *j++ = key;

        assert(j == last);
    }
}

#endif