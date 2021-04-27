#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "smart-ptr/test.h"
#include "sort/test.h"
#include "container/test.h"

int main() {
    Catch::Session().run();
}
