#pragma once

#include <algorithm>

namespace sort {
    class heap_sort {
    public:
        heap_sort() = default;
        heap_sort(const heap_sort& other) = default;
        heap_sort(heap_sort&& other) = default;
        heap_sort& operator = (const heap_sort& other) = default;
        ~heap_sort() = default;

        template< class IterT >
        void sort(IterT first, IterT last) {
        }
    };
}