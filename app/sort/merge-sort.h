#pragma once

#include <algorithm>

namespace sort {
    class merge_sort {
    public:
        merge_sort() = default;
        merge_sort(const merge_sort& other) = default;
        merge_sort(merge_sort&& other) = default;
        merge_sort& operator = (const merge_sort& other) = default;
        ~merge_sort() = default;

        template< class IterT >
        void sort(IterT first, IterT last) {
            if (first == last - 1)
                return;

            auto middle = first + (std::distance(first, last) / 2);
            sort(first, middle);
            sort(middle, last);
            std::inplace_merge(first, middle, last);
        }
    };
}