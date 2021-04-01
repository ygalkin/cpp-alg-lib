#pragma once

// Single-linked list implementation

namespace container {

    template< class KeyT >
    class single_linked_list {
    protected:
        struct list_node {
            list_node() = delete;
            list_node(const KeyT& val) : _val(val), _next(nullptr) {};
            list_node(const list_node& other) = delete;
            list_node(list_node&& other) = default;
            list_node& operator = (const list_node& other) = delete;
            ~list_node() = default;

            list_node* _next = nullptr;
            KeyT _val;
        };

    private:
        list_node* _head = nullptr;

        list_node* _get_node(size_t index) {
            list_node* current = _head;
            auto i{ 0 };

            while (current != nullptr && i != index) {
                ++i;
                current = current->_next;
            }

            if (i != index) {
                return nullptr;
            }

            return current;
        }

    public:
        single_linked_list() = default;
        single_linked_list(const single_linked_list& other) = delete;
        single_linked_list(single_linked_list&& other) = delete;
        single_linked_list& operator = (const single_linked_list& other) = delete;
        ~single_linked_list() { clear(); }

        // Get the value of the index-th node in the linked list. If the index is invalid, return -1.
        KeyT at(size_t index) {
            auto node = _get_node(index);
            if (node == nullptr) {
                throw new std::out_of_range("Index is out of range: " + index);
            }

            return node->_val;
        }

        // Add a node of value val before the first element of the linked list. 
        // After the insertion, the new node will be the first node of the linked list.
        void push_front(const KeyT& val) {
            auto new_node = new list_node(val);

            new_node->_next = _head;
            _head = new_node;
        }

        // Append a node of value val to the last element of the linked list.
        void push_back(const KeyT& val) {
            if (_head == nullptr) {
                push_front(val);
                return;
            }

            auto current = _head;
            while (current->_next != nullptr) {
                current = current->_next;
            }

            current->_next = new list_node(val);
        }

        // Add a node of value val before the index-th node in the linked list. 
        // If index equals to the length of linked list, the node will be appended to the end of linked list. 
        // If index is greater than the length, the node will not be inserted.
        void insert_before(int index, const KeyT& val) {
            if (index == 0) {
                push_front(val);
                return;
            }

            auto prev = _get_node(index - 1); // find previous
            if (prev == nullptr) {
                return;
            }

            auto new_node = new list_node(val);

            new_node->_next = prev->_next;
            prev->_next = new_node;
        }

        // Delete the index-th node in the linked list, if the index is valid.
        void erase(size_t index) {
            auto curr = _get_node(index);
            if (curr == nullptr) {
                return;
            }
            if (index == 0) { // pop_front
                _head = curr->_next;
                delete curr;
                return;
            }

            auto prev = _get_node(index - 1); // find previous
            if (prev == nullptr) {
                return;
            }

            prev->_next = curr->_next;
            delete curr;
        }

        void clear() {
            //todo
        }

        // bool empty
    };

}
