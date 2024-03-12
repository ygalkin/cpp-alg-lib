#ifndef _ALGORITHM_TEST_
#define _ALGORITHM_TEST_

#include "algorithm.h"
#include "string-util.h"

#include <string_view>

namespace algorithm {

    inline constexpr std::pair<std::string_view, std::string_view> TEST_SEARCH_STR{ "Some books are to be tasted, others to be swallowed, and some few to be chewed and digested.", "to" };
    inline constexpr size_t TEST_SEARCH_POS{ 15 };

    TEST_CASE("Naive string-searching algorithm", "[algorithm]") {
        REQUIRE(algorithm::naive_string_search("abc", "") == 0);
        REQUIRE(algorithm::naive_string_search("ab", "abc") == std::string_view::npos);
        REQUIRE(algorithm::naive_string_search(TEST_SEARCH_STR.first, TEST_SEARCH_STR.second) == TEST_SEARCH_POS);
        REQUIRE(algorithm::naive_string_search("abc", "d") == std::string_view::npos);
    }

    TEST_CASE("Knuth–Morris–Pratt string-searching algorithm", "[algorithm]") {
        REQUIRE(algorithm::kmp_string_search("abc", "") == 0);
        REQUIRE(algorithm::kmp_string_search("ab", "abc") == std::string_view::npos);
        // REQUIRE(algorithm::kmp_string_search(TEST_SEARCH_STR.first, TEST_SEARCH_STR.second) == TEST_SEARCH_POS);
        REQUIRE(algorithm::kmp_string_search("abc", "d") == std::string_view::npos);
    }

    TEST_CASE("Palindrome", "[algorithm]") {
        std::string a1{ "racecar" };
        REQUIRE(algorithm::is_palindrome(a1.cbegin(), a1.cend()) == true);
        std::string a2{ "raceecar" };
        REQUIRE(algorithm::is_palindrome(a2.cbegin(), a2.cend()) == true);
        std::string a3{ "test" };
        REQUIRE(algorithm::is_palindrome(a3.cbegin(), a3.cend()) == false);
        std::vector<int> v1{1,2,3,3,2,1};
        REQUIRE(algorithm::is_palindrome(v1.cbegin(), v1.cend()) == true);
        std::vector<int> v2{ 1,2,3,2,1};
        REQUIRE(algorithm::is_palindrome(v2.cbegin(), v2.cend()) == true);
        std::vector<int> v3{ 1,2,3,4,1 };
        REQUIRE(algorithm::is_palindrome(v3.cbegin(), v3.cend()) == false);
    }

    TEST_CASE("roman number", "[algorithm]") {
        REQUIRE(algorithm::roman_to_int("I") == 1);
        REQUIRE(algorithm::roman_to_int("X") == 10);
        REQUIRE(algorithm::roman_to_int("MMXXI") == 2021);
        REQUIRE(algorithm::roman_to_int("") == 0);

        // user defined literal
        REQUIRE("MM"_roman == 2000);
        REQUIRE("MMMM"_roman == 4000);

        // additive notation and subtractive notation
        REQUIRE("XXXXXX"_roman == "LX"_roman);
        REQUIRE("IIIIII"_roman == "VI"_roman);
        REQUIRE("IIII"_roman == "IV"_roman);
    }

    TEST_CASE("string utils", "[algorithm]") {
        REQUIRE(algorithm::string_remove_spaces("Remove All Spaces") == "RemoveAllSpaces");
        REQUIRE(algorithm::string_remove_pattern("Remove#All#Patterns", '#') == "RemoveAllPatterns");
        REQUIRE(algorithm::string_remove_spaces("") == "");
        REQUIRE(algorithm::string_remove_spaces("     ") == "");
        REQUIRE(algorithm::string_remove_pattern("", '#') == "");

        REQUIRE(algorithm::string_join({"a", "b", "c"}, ", ") == "a, b, c");
        REQUIRE(algorithm::string_join({}, ", ") == "");
        REQUIRE(algorithm::string_join({ "a", "b", "c" }, "") == "abc");
    }
}

#endif 
