#pragma once

#include "../binary-search-tree.h"

#include <limits.h>
#include <cassert>

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
            binary_search_tree<IterT::value_type> bst;

            // for [first, last)
            for (auto iter = first; iter != last; ++iter) {
                bst.insert(*iter);
            }

            assert(bst.is_bst(std::numeric_limits<IterT::value_type>::min(), std::numeric_limits<IterT::value_type>::max()));

            auto iter = first;
            bst.for_each<order_type::sort_order>([&iter](const auto &key) { *iter++ = key; });
            assert(iter == last);
            bst.clear();
        }
    };
}