#ifndef _CONTAINER_TEST_
#define _CONTAINER_TEST_

#include "singly-linked-list.h"
#include "binary-search-tree.h"
#include "trie.h"

#include <list>
#include <array>
#include <limits>

namespace container {

    TEST_CASE("binary search tree", "[container]") {
        static constexpr std::array<int, 13> _test_array{ {10, 4, 0, -9, -9, 11, -1,  std::numeric_limits<int>::min(), -2, -1, 33, std::numeric_limits<int>::max(), 11 } };

        binary_search_tree<int> bst;
        REQUIRE(bst.empty());

        for (auto item : _test_array) {
            bst.insert(item);
        }

        std::list<int> arr1;
        bst.for_each<order_type::sort_order>([&arr1](const auto& key) { arr1.push_back(key); });
        REQUIRE(arr1.size() == _test_array.size());
        REQUIRE(bst.size() == _test_array.size());

        std::list<int> arr2;
        size_t level{ 0 };
        bst.for_each_level_order([&arr2, &level](const auto& key, const auto& l) { arr2.push_back(key); level = l; });
        REQUIRE(arr2.size() == _test_array.size());
        REQUIRE(level == 6);

        REQUIRE(bst.is_bst());

        REQUIRE(bst.find(*(end(_test_array) - 1))); // find last element
        REQUIRE(!bst.find(-42));

        REQUIRE(!bst.empty());
        bst.clear();
        REQUIRE(bst.empty());
        REQUIRE(bst.size() == 0);
    }

    TEST_CASE("singly linked list", "[container]") {
        container::singly_linked_list<std::string> sll;
        REQUIRE(sll.empty());

        sll.push_back("test001");
        sll.push_front("test002");
        REQUIRE(sll.insert_before(0, "test003"));
        REQUIRE(!sll.insert_before(10000, ""));

        REQUIRE(!sll.has_cycle());

        REQUIRE(!sll.erase(10000));
        REQUIRE(sll.erase(0));
        sll.push_front("test004");
        REQUIRE(sll.at(0) == "test004");

        REQUIRE(!sll.insert_after(10000, ""));
        REQUIRE(sll.insert_after(0, "test005"));
        REQUIRE(sll.at(1) == "test005");

        std::list<std::string> arr1;
        sll.for_each([&arr1](const auto& val) { arr1.push_back(val); });
        REQUIRE(arr1.size() == 4);

        sll.clear();
        REQUIRE(sll.empty());
    }

    TEST_CASE("trie", "[container]") {
        container::trie t;
        REQUIRE(t.empty());

        t.insert("test001");
        t.insert("test002");
        t.insert("test003");
        REQUIRE(!t.empty());

        REQUIRE(t.search("test001"));
        REQUIRE(!t.search("test0011"));
        REQUIRE(!t.search("test00"));
        t.insert("test00");
        REQUIRE(t.search("test00"));

        REQUIRE(t.starts_with("test"));
        REQUIRE(!t.starts_with("negativetest"));

        t.clear();
        REQUIRE(t.empty());
    }
}

#endif