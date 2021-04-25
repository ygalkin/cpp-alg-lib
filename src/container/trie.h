#pragma once

#include <unordered_map>
#include <memory>
#include <string>

namespace container {

    class trie {
    private:
        struct trie_node {
            trie_node() : _is_complete_word{ false } {};
            ~trie_node() = default;

            std::unordered_map<char, std::unique_ptr<trie_node>> _children;
            bool _is_complete_word;
        };

        std::unique_ptr<trie_node> _root;

        const trie_node* _search(const std::string& word) const {
            trie_node* node = _root.get();

            for (const auto& ch : word) {
                if (node->_children.count(ch) == 0)
                    return nullptr;

                node = node->_children[ch].get();
            }

            return node;
        }

    public:
        trie() { _root = std::make_unique<trie_node>(); }
        virtual ~trie() = default;

        // insert a word into the trie.
        void insert(const std::string& word) {
            trie_node* node = _root.get();

            for (const auto& ch : word) {
                if (node->_children.count(ch) == 0)
                    node->_children[ch] = std::make_unique<trie_node>();

                node = node->_children[ch].get();
            }

            node->_is_complete_word = true;
        }

        // true if the word is in the trie.
        bool search(const std::string& word) const {
            const trie_node* node = _search(word);
            return (node == nullptr) ? false : node->_is_complete_word;
        }

        // true if there is any word in the trie that starts with the given prefix.
        bool starts_with(const std::string& prefix) const {
            const trie_node* node = _search(prefix);
            return !(node == nullptr);
        }

        // TODO
        // clear
        // for_each
        // empty
    };
}