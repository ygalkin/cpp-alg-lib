#if defined(_MSC_VER)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "smart-ptr/test.h"
#include "container/test.h"
#include "algorithm/test.h"
#include "sort/test.h"

int main(int argc, char const* const argv[]) {
#if defined(_MSC_VER)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    Catch::Session().run(argc, argv);
    return 0;
}
