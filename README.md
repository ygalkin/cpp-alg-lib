## Summary 

C++ 23 header-only library. Sorting algorithms, containers, smart pointers.

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

## Searching Algorithms

- naive

## Other Algorithms

- Palindrome

- Roman numeral to int conversion

## Containers

- singly linked list

- binary search tree

- enum array

- trie (prefix tree). Usage: word auto-completion, quick validation if a word is misspelled.

## Smart Pointers

- single_ptr

## String Utilities

- string remove spaces/pattern

- string join

## Benchmark
```
**********[Benchmark: random array]**********
std::sort : time (ms): 11, array size: 100000
std::stable_sort : time (ms): 7, array size: 100000
bubble_sort : time (ms): 12374, array size: 100000
odd_even_sort : time (ms): 8069, array size: 100000
cocktail_shaker_sort : time (ms): 7718, array size: 100000
cocktail_shaker_sort_2 : time (ms): 6856, array size: 100000
selection_sort : time (ms): 929, array size: 100000
selection_sort_2 : time (ms): 937, array size: 100000
selection_sort_3 : time (ms): 8630, array size: 100000
insertion_sort : time (ms): 927, array size: 100000
insertion_sort_2 : time (ms): 2840, array size: 100000
quick_sort : time (ms): 6, array size: 100000
quick_sort_2 : [SKIPPED]
quick_sort_3 : time (ms): 5, array size: 100000
quick_sort_4 : time (ms): 7, array size: 100000
unbalanced_tree_sort : time (ms): 26, array size: 100000
balanced_tree_sort : time (ms): 28, array size: 100000
merge_sort : time (ms): 7, array size: 100000
heap_sort : time (ms): 4, array size: 100000
**********[Benchmark: sorted array]**********
std::sort : time (ms): 0, array size: 100000
std::stable_sort : time (ms): 0, array size: 100000
bubble_sort : time (ms): 0, array size: 100000
odd_even_sort : time (ms): 0, array size: 100000
cocktail_shaker_sort : time (ms): 0, array size: 100000
cocktail_shaker_sort_2 : time (ms): 0, array size: 100000
selection_sort : time (ms): 945, array size: 100000
selection_sort_2 : time (ms): 929, array size: 100000
selection_sort_3 : time (ms): 8686, array size: 100000
insertion_sort : time (ms): 0, array size: 100000
insertion_sort_2 : time (ms): 0, array size: 100000
quick_sort : time (ms): 1, array size: 100000
quick_sort_2 : [SKIPPED]
quick_sort_3 : [SKIPPED]
quick_sort_4 : [SKIPPED]
unbalanced_tree_sort : [SKIPPED]
balanced_tree_sort : time (ms): 16, array size: 100000
merge_sort : time (ms): 1, array size: 100000
heap_sort : time (ms): 3, array size: 100000
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
All tests passed (164 assertions in 15 test cases)
```