#ifndef _ALGORITHM_TEST_
#define _ALGORITHM_TEST_

#include "algorithm.h"

namespace algorithm {

    TEST_CASE("Naive string search", "[algorithm]") {
        REQUIRE(algorithm::naive_string_search("al", "algo") == std::string::npos);
        REQUIRE(algorithm::naive_string_search("abcd", "e") == std::string::npos);
        REQUIRE(algorithm::naive_string_search("pattern search algorithm example", "algo") == 15);
    }
}

#endif 
