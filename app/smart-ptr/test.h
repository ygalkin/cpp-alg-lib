#pragma once

#include "single-ptr.h"

#include <string>
#include <iostream>

namespace smart_ptr {
    class test {
    public:
        test() = default;
        test(const test& other) = delete;
        test(test&& other) = default;
        test& operator = (const test& other) = delete;
        ~test() = default;

        void run() const {
            single_ptr_test_case();
            count_ptr_test_case();
        }

        void single_ptr_test_case() const {
            std::cout << "**********[" << __FUNCTION__ << "]**********" << std::endl;

            single_ptr<std::string> ptr(new std::string("test"));
            auto ptr2 = std::move(ptr);
        }

        void count_ptr_test_case() const {
            std::cout << "**********[" << __FUNCTION__ << "]**********" << std::endl;
        }
    };
}