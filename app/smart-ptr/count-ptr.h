#pragma once

namespace smart_ptr {
    
    // TODO:
    template <typename T>
    class count_ptr {
    public:
        count_ptr() = delete;

        count_ptr(T* ptr) noexcept : 
            _ref_counter{1}, 
            _ptr { ptr } {
        };

        count_ptr(const count_ptr& other) = delete;
        count_ptr& operator = (const count_ptr& other) = delete;
        count_ptr(count_ptr&& other) noexcept : _ptr{ nullptr } = delete;
        count_ptr& operator = (count_ptr&& other) noexcept = delete;

        ~count_ptr() {
            --_ref_counter;
            if (_ref_counter == 0)
                delete _ptr;
        };

    private:
        int _ref_counter = 0;
        T* _ptr = nullptr;
    };
}