## Summary 

C++ 14 header-only library. Sorting algorithms, containers, smart pointers.

## External dependency

Catch2 unit test library - https://github.com/catchorg/Catch2

## Sorting Algorithms using STL iterators

- bubble sort

- odd even sort (variation of bubble sort)

- cocktail shaker sort (bidirectional bubble sort)

- selection sort

- insertion sort

- quick sort

- merge sort

- heap sort

- unbalanced tree sort

- balanced tree sort

## Containers

- singly linked list

- binary search tree

- trie (prefix tree). (Usage: word auto-completion, quick validation if a word is misspelled)

## Smart Pointers

- single_ptr

## Benchmark
```
**********[Benchmark: random array]**********
std::sort : time (ms): 2, array size: 50000
std::stable_sort : time (ms): 2, array size: 50000
bubble_sort : time (ms): 3081, array size: 50000
odd_even_sort : time (ms): 1625, array size: 50000
cocktail_shaker_sort : time (ms): 1667, array size: 50000
cocktail_shaker_sort_2 : time (ms): 1918, array size: 50000
selection_sort : time (ms): 2145, array size: 50000
selection_sort_2 : time (ms): 2142, array size: 50000
selection_sort_3 : time (ms): 2147, array size: 50000
insertion_sort : time (ms): 230, array size: 50000
insertion_sort_2 : time (ms): 683, array size: 50000
quick_sort : time (ms): 3, array size: 50000
quick_sort_2 : [SKIPPED]
quick_sort_3 : time (ms): 2, array size: 50000
quick_sort_4 : time (ms): 3, array size: 50000
unbalanced_tree_sort : time (ms): 12, array size: 50000
balanced_tree_sort : time (ms): 13, array size: 50000
merge_sort : time (ms): 3, array size: 50000
heap_sort : time (ms): 3, array size: 50000
**********[Benchmark: sorted array]**********
std::sort : time (ms): 0, array size: 50000
std::stable_sort : time (ms): 0, array size: 50000
bubble_sort : time (ms): 0, array size: 50000
odd_even_sort : time (ms): 0, array size: 50000
cocktail_shaker_sort : time (ms): 0, array size: 50000
cocktail_shaker_sort_2 : time (ms): 0, array size: 50000
selection_sort : time (ms): 2141, array size: 50000
selection_sort_2 : time (ms): 2140, array size: 50000
selection_sort_3 : time (ms): 2144, array size: 50000
insertion_sort : time (ms): 0, array size: 50000
insertion_sort_2 : time (ms): 0, array size: 50000
quick_sort : time (ms): 0, array size: 50000
quick_sort_2 : [SKIPPED]
quick_sort_3 : [SKIPPED]
quick_sort_4 : [SKIPPED]
unbalanced_tree_sort : [SKIPPED]
balanced_tree_sort : time (ms): 8, array size: 50000
merge_sort : time (ms): 0, array size: 50000
heap_sort : time (ms): 1, array size: 50000
**********[Benchmark: empty array]**********
std::sort : time (ms): 0, array size: 0
std::stable_sort : time (ms): 0, array size: 0
bubble_sort : time (ms): 0, array size: 0
odd_even_sort : time (ms): 0, array size: 0
cocktail_shaker_sort : time (ms): 0, array size: 0
cocktail_shaker_sort_2 : time (ms): 0, array size: 0
selection_sort : time (ms): 0, array size: 0
selection_sort_2 : time (ms): 0, array size: 0
selection_sort_3 : time (ms): 0, array size: 0
insertion_sort : time (ms): 0, array size: 0
insertion_sort_2 : time (ms): 0, array size: 0
quick_sort : time (ms): 0, array size: 0
quick_sort_2 : time (ms): 0, array size: 0
quick_sort_3 : time (ms): 0, array size: 0
quick_sort_4 : time (ms): 0, array size: 0
unbalanced_tree_sort : time (ms): 0, array size: 0
balanced_tree_sort : time (ms): 0, array size: 0
merge_sort : time (ms): 0, array size: 0
heap_sort : time (ms): 0, array size: 0
**********[Benchmark: one element array]**********
std::sort : time (ms): 0, array size: 1
std::stable_sort : time (ms): 0, array size: 1
bubble_sort : time (ms): 0, array size: 1
odd_even_sort : time (ms): 0, array size: 1
cocktail_shaker_sort : [SKIPPED]
cocktail_shaker_sort_2 : time (ms): 0, array size: 1
selection_sort : time (ms): 0, array size: 1
selection_sort_2 : time (ms): 0, array size: 1
selection_sort_3 : time (ms): 0, array size: 1
insertion_sort : time (ms): 0, array size: 1
insertion_sort_2 : time (ms): 0, array size: 1
quick_sort : time (ms): 0, array size: 1
quick_sort_2 : time (ms): 0, array size: 1
quick_sort_3 : time (ms): 0, array size: 1
quick_sort_4 : time (ms): 0, array size: 1
unbalanced_tree_sort : time (ms): 0, array size: 1
balanced_tree_sort : time (ms): 0, array size: 1
merge_sort : time (ms): 0, array size: 1
heap_sort : time (ms): 0, array size: 1
===============================================================================
All tests passed (102 assertions in 8 test cases)
```
