#ifndef _SMART_PTR_TEST_
#define _SMART_PTR_TEST_

#include "single-ptr.h"

#include <string>
#include <functional>

namespace smart_ptr {

    TEST_CASE("single_ptr", "[smart_ptr]") {
        // default deleter
        {
            single_ptr<std::string> ptr1(new std::string("test001"));

            auto ptr2 = std::move(ptr1);
            REQUIRE(ptr1.get() == nullptr);

            ptr2->append("test002");
            (*ptr2).append("test003");

            REQUIRE(ptr2.get()->compare("test001test002test003") == 0);
            //REQUIRE(ptr2.release()->compare("test001test002test003") == 0);
            //REQUIRE(ptr2.get() == nullptr);
            //ptr2.reset(nullptr);
        }

        // custom deleter
        {
            single_ptr<std::string, std::function<void(std::string*)>> custom_ptr(
                new std::string("test001"),
                [](std::string* p) {
                    REQUIRE(p != nullptr);
                    REQUIRE(p->compare("test001") == 0);
                    delete p;
                });
        }
    }
}

#endif