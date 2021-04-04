#pragma once

#include "../container/binary-search-tree.h"

#include <cassert>
#include <set>

namespace sort {
    class tree_sort {
    public:
        tree_sort() = default;
        tree_sort(const tree_sort& other) = default;
        tree_sort(tree_sort&& other) = default;
        tree_sort& operator = (const tree_sort& other) = default;
        ~tree_sort() = default;

        template< class IterT >
        void unbalanced_bst_sort(IterT first, IterT last) {
            container::binary_search_tree<IterT::value_type> bst;

            // for [first, last)
            for (auto iter = first; iter != last; ++iter) {
                bst.insert(*iter);
            }

            auto iter = first;
            bst.for_each<container::order_type::sort_order>([&iter](const auto& key) { *iter++ = key; });
            assert(iter == last);
            bst.clear();
        }

        template< class IterT >
        void multiset_sort(IterT first, IterT last) {
            // multiset implemenation is red-black (balanced) binary search tree
            std::multiset<IterT::value_type> multi_set;

            // for [first, last)
            for (auto iter = first; iter != last; ++iter) {
                multi_set.insert(*iter);
            }

            auto i = first;
            for (auto iter = std::begin(multi_set); iter != std::end(multi_set); ++iter) {
                *i++ = *iter;
            }
            assert(i == last);
        }
    };
}