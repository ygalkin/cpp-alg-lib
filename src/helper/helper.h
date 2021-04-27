#ifndef _HELPER_
#define _HELPER_

#include <algorithm>
#include <iostream>
#include <chrono>

namespace helper {
    template <typename T>
    std::ostream& out_each(std::ostream& os, const T& t) {
        os << "["; std::for_each(begin(t), end(t), [](const auto& i) { std::cout << i << " "; }); os << "]";
        return os;
    }

    template <typename T>
    std::ostream& out_each(std::ostream& os, T first, T last) {
        os << "["; std::for_each(first, last, [](const auto& i) { std::cout << i << " "; }); os << "]";
        return os;
    }

    auto benchmark_call_ms = [](auto&& func) {
        // get time before function invocation
        const auto& start = std::chrono::high_resolution_clock::now();
        // function invocation
        func();
        // get time after function invocation
        const auto& stop = std::chrono::high_resolution_clock::now();

        return std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
    };
}

#endif