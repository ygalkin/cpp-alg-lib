#pragma once

#include "single-ptr.h"

#include <string>
#include <iostream>
#include <cassert>
#include <functional>

namespace smart_ptr {
    class test {
    public:
        test() = default;
        test(const test& other) = delete;
        test(test&& other) = default;
        test& operator = (const test& other) = delete;
        ~test() = default;

        void run() const {
            test_single_ptr();
            test_count_ptr();
        }

        void test_single_ptr() const {
            std::cout << "**********[" << __FUNCTION__ << "]**********" << std::endl;

            // default deleter
            single_ptr<std::string> smart_ptr(new std::string("test1"));
            auto smart_ptr2 = std::move(smart_ptr);
            assert(smart_ptr.get() == nullptr);
            smart_ptr2->append("test2");
            (*smart_ptr2).append("test3");
            auto raw_ptr = smart_ptr2.get();
            std::cout << raw_ptr->c_str() << std::endl;
            std::cout << smart_ptr2.release()->c_str() << std::endl;
            assert(smart_ptr2.get() == nullptr);
            smart_ptr2.reset(nullptr);

            // custom deleter
            single_ptr<std::string, std::function<void(std::string*)>> custom_ptr(
                new std::string("test1"),
                [](std::string* p) { delete p; });
        }

        void test_count_ptr() const {
            std::cout << "**********[" << __FUNCTION__ << "]**********" << std::endl;
        }
    };
}