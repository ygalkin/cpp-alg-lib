#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <string>

namespace algorithm {

    size_t naive_string_search(const std::string& text, const std::string& pattern) {
        if (pattern.empty()) {
            return 0;
        }

        if (text.size() < pattern.size()) {
            return std::string::npos;
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

        return std::string::npos;
    }

    // knuth_morris_pratt_string_search
    size_t kmp_string_search(const std::string& text, const std::string& pattern) {
        if (pattern.empty()) {
            return 0;
        }

        if (text.size() < pattern.size()) {
            return std::string::npos;
        }

        return std::string::npos;
    }

}

#endif