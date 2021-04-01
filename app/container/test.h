#pragma once

#pragma once

#include "single-linked-list.h"
#include "binary-search-tree.h"
#include "../helper.h"

#include<iostream>
#include<list>
#include<array>
#include <limits>
#include <cassert>

namespace container {
    class test {
    public:
        test() = delete;
        test(const test& other) = delete;
        test(test&& other) = default;
        test& operator = (const test& other) = delete;
        ~test() = delete;

        static void run() {
            test_binary_search_tree();
            test_single_linked_list();
        }

    private:
        static constexpr std::array<int, 11> _array{ {10, 4, 0, 11, -1,  std::numeric_limits<int>::min(), -2, -1, 33, std::numeric_limits<int>::max(), 11 } };

        static void test_binary_search_tree() {
            std::cout << "-- BST ---" << std::endl;
            binary_search_tree<int> bst;

            for (auto item : _array) {
                bst.insert(item);
            }

            std::list<int> arr;
            bst.for_each<order_type::sort_order>([&arr](auto& key) { arr.push_back(key); });
            helper::out_each(std::cout, arr) << std::endl;

            assert(bst.is_bst(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()));
            assert(bst.find(33));
            assert(!bst.find(-33));
            assert(!bst.empty());
            bst.clear();
            assert(bst.empty());
        }

        static void test_single_linked_list() {
            std::cout << "-- Single Linked List ---" << std::endl;

            container::single_linked_list<std::string> sll;
            sll.push_back("str001");
            sll.push_front("str002");
            sll.insert_before(0, "str003");
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
