#pragma once

#include <functional>

namespace container {

    enum class order_type { pre_order, in_order, sort_order = in_order, post_order };

    template< class KeyT >
    class binary_search_tree {
    protected:
        template< class KeyT >
        struct tree_node {
            tree_node() = delete;
            tree_node(KeyT key) : _left(nullptr), _right(nullptr), _key(key) {};
            tree_node(const tree_node& other) = delete;
            tree_node(tree_node&& other) = default;
            tree_node& operator = (const tree_node& other) = delete;
            ~tree_node() = default;

            tree_node* _left;
            tree_node* _right;
            KeyT _key;
        };

    private:
        tree_node<KeyT>* _root = nullptr;

        void _insert(tree_node<KeyT>** parent, const KeyT& key) {
            if (*parent == nullptr) {
                *parent = new tree_node<KeyT>(key);
                return;
            }

            _insert((key < (*parent)->_key) ? &(*parent)->_left : &(*parent)->_right, key);
        }

        tree_node<KeyT>* _find(tree_node<KeyT>* parent, const KeyT& key) const {
            if (parent == nullptr || parent->_key == key) {
                return parent; // nullptr or parent
            }
            return _find(key < parent->_key ? parent->_left : parent->_right, key);
        }

        template <order_type Order>
        void _for_each(tree_node<KeyT>* parent, std::function<void(const KeyT&)> f) const {
            if (parent == nullptr) {
                return;
            }

            if (Order == order_type::pre_order) f(parent->_key);
            _for_each<Order>(parent->_left, f);
            if (Order == order_type::in_order) f(parent->_key);
            _for_each<Order>(parent->_right, f);
            if (Order == order_type::post_order) f(parent->_key);
        }

        void _clear_post_order(tree_node<KeyT>* parent) {
            if (parent == nullptr) {
                return;
            }

            _clear_post_order(parent->_left);
            _clear_post_order(parent->_right);
            delete parent;
        }

        bool _is_bst(const tree_node<KeyT>* node, const KeyT& min, const KeyT& max) const {
            if (node == nullptr) {
                return true;
            }

            if (node->_key < min || node->_key > max) {
                return false;
            }

            return _is_bst(node->_left, min, node->_key - 1) && _is_bst(node->_right, node->_key, max);
        }

    public:
        binary_search_tree() = default;
        binary_search_tree(const binary_search_tree& other) = delete;
        binary_search_tree(binary_search_tree&& other) = delete;
        binary_search_tree& operator = (const binary_search_tree& other) = delete;
        ~binary_search_tree() { clear(); }

        template <order_type Order>
        void for_each(std::function<void(const KeyT&)> f) const {
            _for_each<Order>(_root, f);
        }

        void clear() {
            _clear_post_order(_root);
            _root = nullptr;
        }

        void insert(const KeyT& key) {
            _insert(&_root, key);
        }

        bool find(const KeyT& key) const {
            return (_find(_root, key) != nullptr);
        }

        bool empty() const {
            return (_root == nullptr);
        }

        // erase(key)
        // size_type size

        bool is_bst(const KeyT& min, const KeyT& max) const {
            return _is_bst(_root, min, max);
        }
    };

}
