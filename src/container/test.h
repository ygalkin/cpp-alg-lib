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

    static constexpr std::array<int, 13> _test_array{ {10, 4, 0, -9, -9, 11, -1,  std::numeric_limits<int>::min(), -2, -1, 33, std::numeric_limits<int>::max(), 11 } };

    TEST_CASE("binary_search_tree", "[container]") {
        binary_search_tree<int> bst;

        for (auto item : _test_array) {
            bst.insert(item);
        }

        std::list<int> arr;
        bst.for_each<order_type::sort_order>([&arr](auto& key) { arr.push_back(key); });

        REQUIRE(bst.is_bst());
        REQUIRE(bst.find(33));
        REQUIRE(!bst.find(-33));
        REQUIRE(!bst.empty());
        bst.clear();
        REQUIRE(bst.empty());
    }

    TEST_CASE("singly_linked_list", "[container]") {
        container::singly_linked_list<std::string> sll;
        sll.push_back("test001");
        sll.push_front("test002");
        sll.insert_before(0, "test003");
        REQUIRE(!sll.has_cycle());
        sll.clear();
        REQUIRE(sll.empty());
    }

    TEST_CASE("trie", "[container]") {
        container::trie t;

        t.insert("test001");
        t.insert("test002");
        t.insert("test003");
        REQUIRE(t.search("test001"));
        REQUIRE(!t.search("test0011"));
        REQUIRE(t.starts_with("test"));
        REQUIRE(!t.starts_with("negativetest"));
    }
}

#endif