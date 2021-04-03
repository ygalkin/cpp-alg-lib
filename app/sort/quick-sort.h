#pragma once

namespace sort {
    class quick_sort {
    public:
        quick_sort() = default;
        quick_sort(const quick_sort& other) = default;
        quick_sort(quick_sort&& other) = default;
        quick_sort& operator = (const quick_sort& other) = default;
        ~quick_sort() = default;

        template< class IterT >
        void sort(IterT first, IterT last) {
            if (first == last)
                return;

            // Partitioning
            auto pivot = *(last - 1); // pivot element is a last element
            auto partition_iter = first;
            // for [first, last)
            for (auto iter = first; iter != last; ++iter) {
                if (*iter < pivot) {
                    std::iter_swap(partition_iter, iter);
                    ++partition_iter;
                }
            }
            std::iter_swap(partition_iter, last - 1);

            sort(first, partition_iter);
            sort(partition_iter + 1, last);
        }
    };
}