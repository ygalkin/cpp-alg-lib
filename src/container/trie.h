#ifndef _CONTAINER_TRIE_
#define _CONTAINER_TRIE_

#include <unordered_map>
#include <memory>
#include <string>

// Trie (prefix tree). 
// Common usage: 
//      word auto-completion,
//      quick validation if a word misspelled

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
            auto node = _root.get();

            for (const auto& ch : word) {
                if (node->_children.count(ch) == 0)
                    return nullptr;

                node = node->_children[ch].get();
            }

            return node;
        }

    public:
        trie() { _root = std::make_unique<trie_node>(); }
        trie(const trie& other) = delete;
        trie(trie&& other) = delete;
        trie& operator = (const trie& other) = delete;
        trie& operator = (trie&& other) = delete;
        virtual ~trie() = default;

        // insert a word into the trie.
        void insert(const std::string& word) {
            auto node = _root.get();

            for (const auto& ch : word) {
                if (node->_children.count(ch) == 0) {
                    node->_children.emplace(ch, std::make_unique<trie_node>());
                }

                node = node->_children[ch].get();
            }

            node->_is_complete_word = true;
        }

        // true if the word is in the trie.
        bool search(const std::string& word) const {
            const auto node = _search(word);
            return (node == nullptr) ? false : node->_is_complete_word;
        }

        // true if there is any word in the trie that starts with the given prefix.
        bool starts_with(const std::string& prefix) const {
            const auto node = _search(prefix);
            return !(node == nullptr);
        }

        // true if trie is empty
        bool empty() const noexcept {
            return _root->_children.empty();
        }

        void clear() noexcept {
            return _root->_children.clear();
        }
    };
}

#endif