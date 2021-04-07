#pragma once

namespace sort {
    namespace sandbox {

        template< class IterT >
        inline void selection_sort_2(IterT first, IterT last) {
            for (auto iter = first; iter != last; ++iter)
                std::iter_swap(iter, std::min_element(iter, last));
        }

        // The same as selection_sort2() but std::min_element replaced by self-implemented find min element loop
        // DO NOT USE THIS FUNCTION. Slow implemenation. It's used for benchmark only.
        template< class IterT >
        inline void selection_sort_3(IterT first, IterT last) {
            if (first == last)
                return;

            // for [first, last-1)
            const auto prev_last = std::prev(last);
            for (IterT iter_a = first; iter_a != prev_last; ++iter_a) {
                IterT iter_min = iter_a;
                // find min element [iter_a + 1, last)
                for (IterT iter_b = std::next(iter_a); iter_b != last; ++iter_b) {
                    if (*iter_b < *iter_min)
                        iter_min = iter_b;
                }

                std::iter_swap(iter_a, iter_min);
            }
        }

        // DO NOT USE THIS FUNCTION. Slow implemenation. It's used for benchmark only.
        template <typename IterT>
        inline void insertion_sort_2(IterT first, IterT last) {
            if (first == last)
                return;

            // for [first + 1, last)
            for (auto iter = std::next(first); iter != last; ++iter) {
                for (auto iter_curr = iter, iter_prev = std::prev(iter); *iter_prev > *iter_curr; --iter_prev, --iter_curr) {
                    std::iter_swap(iter_prev, iter_curr);
                    if (iter_prev == first)
                        break;
                }
            }
        }

        // DO NOT USE THIS FUNCTION. Slow implemenation. std::partition works much faster than self-implemented partitioning algorithm. 
        // It's used for benchmark only.
        template< class IterT >
        inline void quick_sort_2(IterT first, IterT last) {
            if (first == last)
                return;

            const auto pivot = *(first + (std::distance(first, last) / 2));

            // Partitioning. Hoare partition scheme
            auto left = first;
            auto right = std::prev(last);
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
        // DO NOT USE THIS FUNCTION. Can cause stack overflow. You can use it as Lomuto’s partition scheme reference code. 
        // It's used for benchmark only.
        template< class IterT >
        inline void quick_sort_3(IterT first, IterT last) {
            if (first == last)
                return;

            // Partitioning. Lomuto’s partition scheme
            const auto pivot = std::prev(last); // pivot element is a last element
            auto bound = std::partition(first, last, [&pivot](const auto& i) { return i < *pivot; });
            std::iter_swap(bound, pivot);

            quick_sort_3(first, bound);
            quick_sort_3(std::next(bound), last);
        }

        // ! Stack overflow on a SORTED large array ~ 4000 elements. Replaced by Hoare partition scheme
        // DO NOT USE THIS FUNCTION. Slow implemenation and can cause stack overflow. You can use it as Lomuto’s partition scheme reference code.  
        // It's used for benchmark only.
        template< class IterT >
        inline void quick_sort_4(IterT first, IterT last) {
            if (first == last)
                return;

            // Partitioning. Lomuto’s partition scheme
            const auto pivot = std::prev(last); // pivot element is a last element
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
            quick_sort_4(std::next(bound), last);
        }
    }
}
