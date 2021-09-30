#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <string_view>

namespace algorithm {

    inline size_t naive_string_search(const std::string_view& text, const std::string_view& pattern) {
        if (pattern.empty()) {
            return 0;
        }

        if (text.size() < pattern.size()) {
            return std::string_view::npos;
        }

        for (size_t i = 0; i <= text.size() - pattern.size(); ++i) {
            if (text[i] == pattern[0]) {
                size_t j = 1;
                for (; j < pattern.size(); ++j) {
                    if (text[i + j] != pattern[j]) {
                        break;
                    }
                }

                if (j == pattern.size()) {
                    return i;
                }
            }
        }

        return std::string_view::npos;
    }

    // Knuth–Morris–Pratt string-searching algorithm
    inline size_t kmp_string_search(const std::string_view& text, const std::string_view& pattern) {
        if (pattern.empty()) {
            return 0;
        }

        if (text.size() < pattern.size()) {
            return std::string_view::npos;
        }

        return std::string_view::npos;
    }
}

#endif