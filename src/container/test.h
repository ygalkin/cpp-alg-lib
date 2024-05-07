#ifndef _CONTAINER_TEST_
#define _CONTAINER_TEST_

#include "singly-linked-list.h"
#include "binary-search-tree.h"
#include "trie.h"
#include "enum-array.h"

#include <list>
#include <array>
#include <limits>

namespace container {

    namespace {
        enum class color_enum {
            RED, // must be 0 based
            GREEN,
            BLUE,
            SIZE, // last valid item. size of the array
            YELLOW // usage of this item triggers static_assert
        };
    }

    TEST_CASE("binary search tree", "[container]") {
        static constexpr std::array<int, 13> TEST_ARRAY{ {10, 4, 0, -9, -9, 11, -1,  std::numeric_limits<int>::min(), -2, -1, 33, std::numeric_limits<int>::max(), 11 } };
        binary_search_tree<int> bst;
        REQUIRE(bst.empty());

        for (const auto& item : TEST_ARRAY) {
            bst.insert(item);
        }

        std::list<int> arr1;
        bst.for_each<order_type::sort_order>([&arr1](const auto& key) { arr1.push_back(key); });
        REQUIRE(arr1.size() == TEST_ARRAY.size());
        REQUIRE(bst.size() == TEST_ARRAY.size());

        std::list<int> arr2;
        size_t level{ 0 };
        bst.for_each_level_order([&arr2, &level](const auto& key, const auto& l) { arr2.push_back(key); level = l; });
        REQUIRE(arr2.size() == TEST_ARRAY.size());
        REQUIRE(level == 6);

        REQUIRE(bst.find(*(end(TEST_ARRAY) - 1))); // find the last element
        REQUIRE(!bst.find(-42));

        REQUIRE(bst.is_bst());
        REQUIRE(bst.height() == 7);
        REQUIRE(bst.diameter() == 9);
        REQUIRE(!bst.is_balanced());

        REQUIRE(!bst.empty());
        bst.clear();
        REQUIRE(bst.empty());
        REQUIRE(bst.size() == 0);
        REQUIRE(bst.diameter() == 0);
        REQUIRE(bst.height() == 0);
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

        std::for_each(sll.begin(), sll.end(), [](auto& val) { val = "10"; });
        for (auto& i : sll) {
            std::cout << i << std::endl;
        }

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

        t.insert("algorithm");
        t.insert("zero");
        t.insert("algo");

        std::list<std::string> arr1;
        t.for_each("test", [&arr1](const auto& word) { arr1.push_back(std::string{ word }); }); // TODO
        REQUIRE(arr1.size() == 4);

        t.clear();
        REQUIRE(t.empty());
    }

    TEST_CASE("enum array. Default ctor", "[container]") {
        enum_array<std::string, color_enum> arr;

        // check default values
        REQUIRE(arr.at<color_enum::BLUE>() == "");
        REQUIRE(arr.at<color_enum::GREEN>() == "");
        REQUIRE(arr.at<color_enum::RED>() == "");

        // modify values
        arr.at<color_enum::RED>() = "red";
        arr.at<color_enum::GREEN>() = "green";
        arr.at<color_enum::BLUE>() = "blue";

        // check modified values
        REQUIRE(arr.at<color_enum::BLUE>() == "blue");
        REQUIRE(arr.at<color_enum::GREEN>() == "green");
        REQUIRE(arr.at<color_enum::RED>() == "red");

        // check const "at"
        const auto r = arr.at<color_enum::BLUE>();
        REQUIRE(r == "blue");

        // check array size
        REQUIRE(arr.size() == 3);

        arr[color_enum::RED] = "red";
        arr[color_enum::GREEN] = "green";
        arr[color_enum::BLUE] = "blue";

        REQUIRE(arr[color_enum::BLUE] == "blue");
        REQUIRE(arr[color_enum::GREEN] == "green");
        REQUIRE(arr[color_enum::RED] == "red");

        bool res = false;
        try {
            auto elem = arr[color_enum::YELLOW];
        }
        catch (std::out_of_range) {
            res = true;
        }
        REQUIRE(res);
    }

    TEST_CASE("enum array. No default ctor", "[container]") {
        class color {
        public:
            color() = delete;
            ~color() = default;
            explicit color(std::string_view name) : _name{ name } {
            }
            std::string name() const {
                return _name;
            }
        private:
            std::string _name;
        };

        enum_array<color, color_enum> arr{ color{"Default"} };

        // check default values
        REQUIRE(arr.at<color_enum::BLUE>().name() == "Default");
        REQUIRE(arr.at<color_enum::GREEN>().name() == "Default");
        REQUIRE(arr.at<color_enum::RED>().name() == "Default");

        // modify values
        arr.at<color_enum::BLUE>() = color{ "blue" };
        arr.at<color_enum::GREEN>() = color{ "green" };
        arr.at<color_enum::RED>() = color{ "red" };

        // check modified values
        REQUIRE(arr.at<color_enum::BLUE>().name() == "blue");
        REQUIRE(arr.at<color_enum::GREEN>().name() == "green");
        REQUIRE(arr.at<color_enum::RED>().name() == "red");
    }
}

#endif