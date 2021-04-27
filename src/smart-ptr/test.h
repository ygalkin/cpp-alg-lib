#ifndef _SMART_PTR_TEST_
#define _SMART_PTR_TEST_

#include "single-ptr.h"

#include <string>
#include <functional>

namespace smart_ptr {

    TEST_CASE("single_ptr", "[smart_ptr]") {
        // default deleter
        single_ptr<std::string> smart_ptr(new std::string("test1"));
        auto smart_ptr2 = std::move(smart_ptr);
        REQUIRE(smart_ptr.get() == nullptr);
        smart_ptr2->append("test2");
        (*smart_ptr2).append("test3");
        auto raw_ptr = smart_ptr2.get();
        smart_ptr2.release();
        REQUIRE(smart_ptr2.get() == nullptr);
        smart_ptr2.reset(nullptr);

        // custom deleter
        single_ptr<std::string, std::function<void(std::string*)>> custom_ptr(
            new std::string("test1"),
            [](std::string* p) { delete p; });
    }
}

#endif