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
    // Bubble sort is a simple sorting algorithm that works by repeatedly stepping through the list, 
    // comparing adjacent elements, and swapping them if they are in the wrong order. The algorithm gets 
    // its name because with each pass through the list, smaller elements "bubble" to the top, 
    // gradually moving towards their correct positions.
    template< class IterT >
    inline void bubble_sort(IterT first, IterT last) {
        if (first == last) {
            return;
        }

        // for [last, first)
        for (auto i = last; i != first; --i) {
            bool is_swapped{ false };
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

            if (!is_swapped) {
                break;
            }
        }
    }

    // Odd Even sort (Brick sort). It's a variation of Bubble sort.
    template< class IterT >
    inline void odd_even_sort(IterT first, IterT last) {
        if (first == last) {
            return;
        }

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

    // Cocktail shaker sort. Bidirectional Bubble sort.
    // Cocktail shaker sort, is a variation of the bubble sort algorithm. It works by repeatedly
    // stepping through the list of elements in both directions, comparing adjacent elements,
    // and swapping them if they are in the wrong order.
    template< class IterT >
    inline void cocktail_shaker_sort(IterT first, IterT last) {
        if (first == last) {
            return;
        }

        bool is_swapped{ true };
        for (auto begin{ first }, end{ std::prev(last) }; is_swapped; ++begin, --end) {
            is_swapped = false;
            // In this optimized version, we use a single loop to perform both forward and reverse passes through the array. 
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
    // Selection sort is called "selection" sort because it repeatedly selects the smallest (or largest) element 
    // from the unsorted part of the list and moves it to its correct position in the sorted part of the list. 
    // Selection sort is not very efficient, especially for large lists, as its time complexity is O(n^2)sort.
    template< class IterT >
    inline void selection_sort(IterT first, IterT last) {
        if (first == last) {
            return;
        }

        // for [first, last-1)
        const auto end = std::prev(last);
        for (auto i = first; i != end; ++i) {
            // find min element [i + 1, last)
            const auto min = std::min_element(std::next(i), last);
            if (*min < *i) {
                std::iter_swap(i, min);
            }
        }
    }

    // Insertion Sort
    // Time complexity: Worst  n^2, Average n^2, Best n
    // Space complexity : 1
    // Stable : Yes
    // Insertion sort is called "insertion" sort because it inserts each element into its correct position in the sorted sublist. 
    template <typename IterT>
    inline void insertion_sort(IterT first, IterT last) {
        if (first == last) {
            return;
        }

        // for [first + 1, last)
        for (auto i = std::next(first); i != last; ++i) {
            auto val{ std::move(*i) };
            auto hole{ i };
            for (auto j = std::prev(i); *j > val; --j) {
                *hole = std::move(*j);
                hole = j;
                if (j == first) {
                    break;
                }
            }

            //if (*hole != val)
            *hole = std::move(val);
        }
    }

    // Quick Sort
    // Quick sort is a sorting algorithm that works by selecting a 'pivot' element from the array and partitioning 
    // the other elements into two sub-arrays according to whether they are less than or greater than the pivot. 
    // The sub-arrays are then recursively sorted. 
    // Quick sort is a divide-and-conquer algorithm, meaning it breaks the problem into smaller sub-problems, 
    // solves them independently, and then combines the solutions. It's known for its efficiency, particularly 
    // for large datasets. However, its worst-case time complexity is O(n^2) when the pivot selection 
    // consistently results in highly unbalanced partitions.
    template< class IterT >
    inline void quick_sort(IterT first, IterT last) {
        if (first == last) {
            return;
        }

        // Partitioning. 3-way partitioning scheme
        const auto pivot = *std::next(first, (std::distance(first, last) / 2));
        // TODO: implement one loop instead of 2 std::partition calls 
        auto bound1 = std::partition(first, last, [&pivot](const auto& i) { return i < pivot; });
        auto bound2 = std::partition(bound1, last, [&pivot](const auto& i) { return (i == pivot); });

        quick_sort(first, bound1);
        quick_sort(bound2, last);
    }

    // Merge Sort
    // Merge sort is a sorting algorithm that works by dividing the unsorted list into smaller sublists, 
    // sorting each sublist, and then merging them back together to produce a sorted list.
    // Merge sort is a stable sorting algorithm, meaning that it preserves the relative order of equal elements. 
    // It has a time complexity of O(n log n), making it efficient 
    // for sorting large lists. Additionally, merge sort is a good choice for sorting linked lists, 
    // as it does not require random access to elements.
    template< class IterT >
    inline void merge_sort(IterT first, IterT last) {
        if (first == last) { // empty sequence to sort
            return;
        }

        // if (first == last - 1)
        if (first == std::prev(last)) { // just one element in a sequence
            return;
        }

        auto middle = std::next(first, (std::distance(first, last) / 2));
        merge_sort(first, middle);
        merge_sort(middle, last);
        // merges two consecutive sorted ranges [first, middle) and [middle, last) into one sorted range [first, last).
        // this function attempts to allocate a temporary buffer. If the allocation fails, the less efficient algorithm is chosen.
        std::inplace_merge(first, middle, last);
    }

    // Heap Sort
    // Heap sort is a sorting algorithm that works by using a special kind of binary tree called a heap.
    // Heap sort has a time complexity of O(n log n). 
    // It is a comparison-based sorting algorithm and is often used when a stable sorting algorithm 
    // (maintains the relative order of equal elements) with better worst-case time complexity than 
    // other comparison-based sorting algorithms like quicksort or mergesort is needed.
    template< class IterT, class Compare>
    inline void heap_sort(IterT first, IterT last, Compare comp) {
        if (first == last) {
            return;
        }

        std::make_heap(first, last, comp);
        std::sort_heap(first, last, comp);
    }

    template< class IterT >
    inline void heap_sort(IterT first, IterT last) {
        heap_sort(first, last, std::less<>{});
    }

    // Tree Sort
    // Tree sort is a sorting algorithm that uses a binary search tree data structure to sort elements. 
    // Tree sort has an average and worst-case time complexity of O(n log n). 
    // However, the time complexity can degrade to O(n^2) in the worst case if the binary search tree becomes unbalanced. 
    template< class IterT >
    inline void unbalanced_tree_sort(IterT first, IterT last) {
        if (first == last) {
            return;
        }

        container::binary_search_tree<typename IterT::value_type> bst;

        // We need this pivot element to improve perfomance of sorted/reverse sorted array
        const auto pivot = std::next(first, (std::distance(first, last) / 2));
        std::iter_swap(first, pivot);

        // for [first, last)
        for (auto i = first; i != last; ++i) {
            bst.insert(*i);
        }

        auto j{ first };
        bst.for_each<container::order_type::sort_order>([&j](const auto& key) { *j++ = key; });
        assert(j == last);
        bst.clear();
    }

    template< class IterT >
    inline void balanced_tree_sort(IterT first, IterT last) {
        if (first == last) {
            return;
        }

        // multiset implemenation is red-black (balanced) binary search tree
        std::multiset<typename IterT::value_type> balanced_bst;

        // for [first, last)
        for (auto i = first; i != last; ++i) {
            balanced_bst.insert(*i);
        }

        auto j{ first };
        for (const auto& key : balanced_bst) {
            *j++ = key;
        }

        assert(j == last);
    }
}

#endif