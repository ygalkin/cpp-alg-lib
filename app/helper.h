#pragma once

#include <algorithm>
#include <iostream>

namespace helper {
    template <typename T>
    std::ostream& out_each(std::ostream& os, const T& t) {
        os << "{";
        std::for_each(begin(t), end(t), [](auto i) { std::cout << i << " "; });
        os << "}";
        return os;
    }
}
