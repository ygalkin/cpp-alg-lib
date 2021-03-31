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
        }
    };
}