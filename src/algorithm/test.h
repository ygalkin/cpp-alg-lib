#ifndef _ALGORITHM_TEST_
#define _ALGORITHM_TEST_

#include "algorithm.h"

namespace algorithm {

    TEST_CASE("roman number", "[algorithm]") {
        REQUIRE(algorithm::roman_to_int("I") == 1);
        REQUIRE(algorithm::roman_to_int("X") == 10);
        REQUIRE(algorithm::roman_to_int("MMXXI") == 2021);

        // user defined literal
        REQUIRE("MM"_roman == 2000);
        REQUIRE("MMMM"_roman == 4000);        

        // additive notation and subtractive notation
        REQUIRE("XXXXXX"_roman == "LX"_roman);
        REQUIRE("IIIIII"_roman == "VI"_roman);
        REQUIRE("IIII"_roman == "IV"_roman);
    }
}

#endif 
