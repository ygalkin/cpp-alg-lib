#pragma once

#include <functional>
#include <iostream>

enum order_type { pre_order, in_order, sort_order=in_order, post_order };

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
        ~tree_node() { }

        tree_node* _left;
        tree_node* _right;
        KeyT _key;
    };

private:
    tree_node<KeyT>* _root = nullptr;

    tree_node<KeyT>* _find_node(tree_node<KeyT>* parent, KeyT key) {
        auto child = (key < parent->_key) ? parent->_left : parent->_right;
        if (child == nullptr) {
            return parent;
        }

        return _find_node(child, key);
    }

    template <order_type Order>
    void _for_each(tree_node<KeyT>* parent, std::function<void(KeyT)> f) const {
        if (parent == nullptr) {
            return;
        }

        if (Order == pre_order) f(parent->_key);
        _for_each<Order>(parent->_left, f);
        if (Order == in_order) f(parent->_key);
        _for_each<Order>(parent->_right, f);
        if (Order == post_order) f(parent->_key);
    }

    void _clear_post_order(tree_node<KeyT>* parent) {
        if (parent == nullptr) {
            return;
        }

        _clear_post_order(parent->_left);
        _clear_post_order(parent->_right);
        delete parent;
    }

    bool _is_bst(tree_node<KeyT>* node, KeyT min, KeyT max) const {
        if (node == nullptr) {
            return true;
        }

        if (node->_key < min || node->_key > max) {
            return false;
        }

        return _is_bst(node->_left, min, node->_key) && _is_bst(node->_right, node->_key, max);
    }

public:
    binary_search_tree() {}
    binary_search_tree(const binary_search_tree& other) = delete;
    binary_search_tree(binary_search_tree&& other) = delete;
    binary_search_tree& operator = (const binary_search_tree& other) = delete;
    ~binary_search_tree() { clear(); }

    template <order_type Order>
    void for_each(std::function<void(KeyT)> f) const {
        _for_each<Order>(_root, f);
    }

    void clear() {
        _clear_post_order(_root);
        _root = nullptr;
    }

    void insert(KeyT key) {
        if (_root == nullptr) {
            _root = new tree_node<KeyT>(key);
            return;
        }

        auto node = _find_node(_root, key);
        auto child = (key < node->_key) ? &node->_left : &node->_right;
        *child = new tree_node<KeyT>(key);
    }

    // bool find(key)
    // erase(key)
    // bool empty
    // size_type size

    bool is_bst(KeyT min, KeyT max) const {
        return _is_bst(_root, min, max);
    }
};
