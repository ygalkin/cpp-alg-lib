#pragma once

#include "single-ptr.h"

#include <string>
#include <iostream>
#include <cassert>
#include <functional>
#include <cstdio>
#include <fstream>



#pragma warning(disable:4996)

namespace smart_ptr {

    //void close_file(std::FILE* fp) {
    //    std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!";
    //    std::fclose(fp);
    //}

    class test {
    public:
        test() = default;
        test(const test& other) = delete;
        test(test&& other) = default;
        test& operator = (const test& other) = delete;
        test& operator = (test&& other) = delete;
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

            //std::ofstream("c:\\temp\\demo1.txt") << 'x';
            ////std::unique_ptr<std::FILE, decltype(&close_file)> fp(std::fopen("c:\\temp\\demo1.txt", "r"), &close_file);
            //single_ptr<std::FILE, decltype(&close_file)> fp(std::fopen("c:\\temp\\demo1.txt", "r"), &close_file);
            //std::FILE* k = fp.get();
        }

        void test_count_ptr() const {
            std::cout << "**********[" << __FUNCTION__ << "]**********" << std::endl;
        }
    };
}