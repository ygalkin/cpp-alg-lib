#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <cctype>
#include <unordered_map>

namespace algorithm {

    unsigned int roman_to_int(const std::string& s) {
        const std::unordered_map<char, int> lookup_tbl = {
            {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
            {'C', 100}, {'D', 500}, {'M', 1000}
        };

        unsigned int n{ 0 };
        int i{ 0 };
        auto prev{ 0 };
        auto curr{ 0 };
        const size_t last = s.size() - 1;

        for (i = last; i >= 0; --i) {
            curr = lookup_tbl.at(s[i]);
            n = (i < last) && (curr < prev) ? n - curr : n + curr;
            prev = curr;
        }

        return n;
    }

    // user defined literal
    unsigned int operator"" _roman(const char* str, size_t /*size*/) {
        return roman_to_int({ str });
    }
}

#endif