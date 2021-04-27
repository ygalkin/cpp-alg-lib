#ifndef _CONTAINER_TEST_
#define _CONTAINER_TEST_

#include "singly-linked-list.h"
#include "binary-search-tree.h"
#include "trie.h"

#include<iostream>
#include<list>
#include<array>
#include<limits>

namespace container {
    TEST_CASE("Container") {

        static constexpr std::array<int, 13> _test_array{ {10, 4, 0, -9, -9, 11, -1,  std::numeric_limits<int>::min(), -2, -1, 33, std::numeric_limits<int>::max(), 11 } };

        SECTION("binary_search_tree") {
            std::cout << "**********[" << __FUNCTION__ << "]**********" << std::endl;

            binary_search_tree<int> bst;

            for (auto item : _test_array) {
                bst.insert(item);
            }

            std::list<int> arr;
            bst.for_each<order_type::sort_order>([&arr](auto& key) { arr.push_back(key); });
            helper::out_each(std::cout, arr) << std::endl;

            REQUIRE(bst.is_bst());
            REQUIRE(bst.find(33));
            REQUIRE(!bst.find(-33));
            REQUIRE(!bst.empty());
            bst.clear();
            REQUIRE(bst.empty());
        }

        SECTION("singly_linked_list") {
            std::cout << "**********[" << __FUNCTION__ << "]**********" << std::endl;

            container::singly_linked_list<std::string> sll;
            sll.push_back("str001");
            sll.push_front("str002");
            sll.insert_before(0, "str003");
            REQUIRE(!sll.has_cycle());
            auto i = sll.at(0);
            std::cout << i << std::endl;
            i = sll.at(1);
            std::cout << i << std::endl;
            i = sll.at(2);
            std::cout << i << std::endl;
            sll.erase(2);
            sll.clear();
            REQUIRE(sll.empty());
        }

        SECTION("Trie") {
            std::cout << "**********[" << __FUNCTION__ << "]**********" << std::endl;

            container::trie t;

            t.insert("test001");
            t.insert("test002");
            t.insert("test003");
            REQUIRE(t.search("test001"));
            REQUIRE(t.starts_with("test"));
        }
    }
}

#endif