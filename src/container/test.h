#pragma once

#pragma once

#include "singly-linked-list.h"
#include "binary-search-tree.h"
#include "../helper/helper.h"

#include<iostream>
#include<list>
#include<array>
#include<limits>
#include<cassert>

namespace container {
    class test {
    public:
        test() = default;
        test(const test& other) = delete;
        test(test&& other) = default;
        test& operator = (const test& other) = delete;
        test& operator = (test&& other) = delete;
        ~test() = default;

        void run() {
            test_binary_search_tree();
            test_singly_linked_list();
        }

    private:
        static constexpr std::array<int, 13> _test_array{ {10, 4, 0, -9, -9, 11, -1,  std::numeric_limits<int>::min(), -2, -1, 33, std::numeric_limits<int>::max(), 11 } };

        void test_binary_search_tree() {
            std::cout << "**********[" << __FUNCTION__ << "]**********" << std::endl;
            binary_search_tree<int> bst;

            for (auto item : _test_array) {
                bst.insert(item);
            }

            std::list<int> arr;
            bst.for_each<order_type::sort_order>([&arr](auto& key) { arr.push_back(key); });
            helper::out_each(std::cout, arr) << std::endl;

            assert(bst.is_bst());
            assert(bst.find(33));
            assert(!bst.find(-33));
            assert(!bst.empty());
            bst.clear();
            assert(bst.empty());
        }

        void test_singly_linked_list() {
            std::cout << "**********[" << __FUNCTION__ << "]**********" << std::endl;

            container::singly_linked_list<std::string> sll;
            sll.push_back("str001");
            sll.push_front("str002");
            sll.insert_before(0, "str003");
            assert(!sll.has_cycle());
            auto i = sll.at(0);
            std::cout << i;
            i = sll.at(1);
            std::cout << i;
            i = sll.at(2);
            std::cout << i;
            sll.erase(2);
            sll.clear();
            assert(sll.empty());
        }
    };
}
