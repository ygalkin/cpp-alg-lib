#ifndef _CONTAINER_BINARY_SEARCH_TREE_
#define _CONTAINER_BINARY_SEARCH_TREE_

#include <functional>

// Binary search tree implementation

namespace container {

    enum class order_type { pre_order, in_order, sort_order = in_order, post_order };

    template< class KeyT >
    class binary_search_tree {
    protected:
        template< class NodeKeyT >
        struct tree_node {
            tree_node() = delete;
            tree_node(const NodeKeyT& key) : _left{ nullptr }, _right{ nullptr }, _key{ key } {};
            tree_node(const tree_node& other) = delete;
            tree_node(tree_node&& other) = delete;
            tree_node& operator = (const tree_node& other) = delete;
            tree_node& operator = (tree_node&& other) = delete;
            ~tree_node() = default;

            tree_node<NodeKeyT>* _left;
            tree_node<NodeKeyT>* _right;
            NodeKeyT _key;
        };

    private:
        tree_node<KeyT>* _root{ nullptr };
        size_t _size{ 0 };

        void _insert(tree_node<KeyT>** parent, const KeyT& key) {
            if (*parent == nullptr) {
                *parent = new tree_node<KeyT>(key);
                ++_size;
                return;
            }

            _insert((key < (*parent)->_key) ? &(*parent)->_left : &(*parent)->_right, key);
        }

        tree_node<KeyT>* _find(tree_node<KeyT>* parent, const KeyT& key) const noexcept {
            if (parent == nullptr || parent->_key == key) {
                return parent; // nullptr or parent
            }
            return _find(key < parent->_key ? parent->_left : parent->_right, key);
        }

        template <order_type Order>
        void _for_each(tree_node<KeyT>* parent, std::function<void(const KeyT&)> f) const noexcept {
            if (parent == nullptr) {
                return;
            }

            if (Order == order_type::pre_order) f(parent->_key);
            _for_each<Order>(parent->_left, f);
            if (Order == order_type::in_order) f(parent->_key);
            _for_each<Order>(parent->_right, f);
            if (Order == order_type::post_order) f(parent->_key);
        }

        void _for_each_level_order(tree_node<KeyT>* root, std::function<void(const KeyT&, const size_t&)> f) const {
            if (root == nullptr) {
                return;
            }

            // 0 is a root level
            size_t level{ 0 };
            std::vector<decltype(root)> q; // std::queue can be used instead

            q.push_back(root);
            while (!q.empty()) {
                const auto size = q.size(); // because we change q size in the loop
                for (auto i = 0; i < size; ++i) {
                    const auto node = q[i];
                    if (node->_left) q.push_back(node->_left);
                    if (node->_right) q.push_back(node->_right);
                    f(node->_key, level);
                }

                ++level;
                q.erase(std::begin(q), std::begin(q) + size);
            }
        }

        void _clear_post_order(tree_node<KeyT>* parent) {
            if (parent == nullptr) {
                return;
            }

            _clear_post_order(parent->_left);
            _clear_post_order(parent->_right);
            delete parent;
        }

        bool _is_bst(const tree_node<KeyT>* node, const tree_node<KeyT>* min, const tree_node<KeyT>* max) const noexcept {
            if (node == nullptr) {
                return true;
            }

            if ((min && node->_key < min->_key) || (max && node->_key > max->_key)) {
                return false;
            }

            return _is_bst(node->_left, min, node) && _is_bst(node->_right, node, max);
        }

        size_t _diameter(const tree_node<KeyT>* node, size_t& diameter) const noexcept {
            if (node == nullptr) {
                return 0;
            }

            auto left = _diameter(node->_left, diameter);
            auto right = _diameter(node->_right, diameter);
            diameter = std::max(diameter, left + right);

            return std::max(left, right) + 1;
        }

        // one pass, post-order
        bool _is_balanced(const tree_node<KeyT>* node, size_t& height) const noexcept {
            if (node == nullptr) {
                height = 0;
                return true;
            }

            size_t lh{ 0 };
            size_t rh{ 0 };
            if (!_is_balanced(node->_left, lh) || !_is_balanced(node->_right, rh)) {
                return false;
            }

            height = std::max(lh, rh) + 1;
            return std::abs(static_cast<int>(lh - rh)) <= 1;
        }

    public:
        binary_search_tree() = default;
        binary_search_tree(const binary_search_tree& other) = delete;
        binary_search_tree(binary_search_tree&& other) = delete;
        binary_search_tree& operator = (const binary_search_tree& other) = delete;
        binary_search_tree& operator = (binary_search_tree&& other) = delete;
        virtual ~binary_search_tree() { clear(); }

        // pre-order, in-order (sort-order), post-order tree traversal (DFS)
        // O(n)
        template <order_type Order>
        void for_each(std::function<void(const KeyT&)> f) const noexcept {
            _for_each<Order>(_root, f);
        }

        // level order tree traversal (BFS)
        // O(n)
        void for_each_level_order(std::function<void(const KeyT&, const size_t&)> f) const {
            _for_each_level_order(_root, f);
        }

        // O(logN)
        void insert(const KeyT& key) {
            _insert(&_root, key);
        }

        // O(logN)
        bool find(const KeyT& key) const noexcept {
            return (_find(_root, key) != nullptr);
        }

        // O(1)
        size_t size() const noexcept {
            return _size;
        }

        // O(1)
        bool empty() const noexcept {
            return (_root == nullptr);
        }

        // O(n)
        void clear() {
            _clear_post_order(_root);
            _root = nullptr;
            _size = 0;
        }

        // Validate if tree is a binary search tree
        bool is_bst() const noexcept {
            return _is_bst(_root, nullptr, nullptr);
        }

        // The diameter of a binary tree is the length of the longest path between any two nodes in a tree. 
        // This path may or may not pass through the root.
        size_t diameter() const noexcept {
            size_t diameter{ 0 };
            _diameter(_root, diameter);

            return diameter;
        }

        // Determine if it is height-balanced - the left and right subtrees of every node differ in height by no more than 1.
        bool is_balanced() const noexcept {
            size_t height{ 0 };
            return _is_balanced(_root, height);
        }
    };
}

#endif
