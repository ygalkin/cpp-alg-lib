#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <functional>
#include <string_view>
#include <unordered_map>

namespace algorithm {

    inline size_t naive_string_search(const std::string_view text, const std::string_view pattern) {
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

    // Knuth-Morris-Pratt string-searching algorithm
    inline size_t kmp_string_search(const std::string_view text, const std::string_view pattern) {
        if (pattern.empty()) {
            return 0;
        }

        if (text.size() < pattern.size()) {
            return std::string_view::npos;
        }

        return std::string_view::npos;
    }

    template< class IterT, class Compare >
    inline bool is_palindrome(IterT first, IterT last, Compare cmp) {
        for (; (first != last) && (first != --last); ++first) {
           if (!cmp(*first, *last)) {
                return false;
            }
        }

        return true;
    }

    template< class IterT >
    inline bool is_palindrome(IterT first, IterT last) {
        return is_palindrome(first, last, std::equal_to<>{});
    }

    inline unsigned int roman_to_int(const std::string_view s) {
        if (s.empty()) {
            return 0;
        }

        static const std::unordered_map<char, int> lookup_tbl{
            {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
            {'C', 100}, {'D', 500}, {'M', 1000}
        };

        unsigned int n{ 0 };
        const size_t last{ s.size() - 1 };

        for (int i = last, prev = 0, curr = 0; i >= 0; --i) {
            curr = lookup_tbl.at(s[i]);
            n = (i < last) && (curr < prev) ? n - curr : n + curr;
            prev = curr;
        }

        return n;
    }

    // user defined literal
    inline unsigned int operator"" _roman(const char* str, size_t /*size*/) {
        return roman_to_int(str);
    }
}

#endif