#pragma once

#include<algorithm>

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
            const auto pivot = *(last - 1); // pivot element is a last element
            auto bound = std::partition(first, last, [&pivot](const auto& i) { return i < pivot; });
            std::iter_swap(bound, last - 1);

            sort(first, bound);
            sort(bound + 1, last);
        }

        template< class IterT >
        void sort2(IterT first, IterT last) {
            if (first == last)
                return;

            // Partitioning
            const auto pivot = *(last - 1); // pivot element is a last element
            auto bound = first;
            // for [first, last)
            for (auto iter = first; iter != last; ++iter) {
                if (*iter < pivot) {
                    std::iter_swap(bound, iter);
                    ++bound;
                }
            }
            std::iter_swap(bound, last - 1);

            sort2(first, bound);
            sort2(bound + 1, last);
        }

    };
}