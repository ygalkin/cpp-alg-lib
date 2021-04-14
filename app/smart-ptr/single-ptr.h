#pragma once

namespace smart_ptr {

    // TODO:
    template <typename T>
    class single_ptr {
    public:
        single_ptr() = delete;

        single_ptr(T* ptr) noexcept : _ptr{ ptr } {
        };

        // non copy constructible
        single_ptr(const single_ptr& other) = delete;
        // non copy assignable
        single_ptr& operator = (const single_ptr& other) = delete;

        // movable
        single_ptr(single_ptr&& other) noexcept : _ptr{ nullptr } {
            _ptr = other._ptr;
            other._ptr = nullptr;
        };

        single_ptr& operator = (single_ptr&& other) noexcept {
            if (this != &other) {
                delete _ptr;
                _ptr = other._ptr;
                other._ptr = nullptr;
            }

            return *this;
        };

        ~single_ptr() {
            delete _ptr;
        };

    private:
        T* _ptr = nullptr;
    };
}
