#pragma once

#pragma once

#include "../helper.h"
#include "binary-search-tree.h"

#include<iostream>
#include<list>
#include<array>

#include <limits.h>
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
    };

}
