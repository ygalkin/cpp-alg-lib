#ifndef _SMART_PTR_SINGLE_PTR_
#define _SMART_PTR_SINGLE_PTR_

#include <functional>

namespace smart_ptr {

    // default deleter
    template <typename T>
    struct default_deleter {
        void operator() (T* p) {
            delete p;
        }
    };

    template <typename T, typename Deleter = default_deleter<T>>
    class single_ptr {
    public:
        using pointer = T*;
        using element_type = T;
        using deleter_type = Deleter;

        single_ptr() = delete;
        single_ptr(T* ptr) noexcept : _ptr{ ptr } {}
        single_ptr(T* ptr, Deleter d) noexcept : _ptr{ ptr }, _deleter{ d } {}
        single_ptr(const single_ptr& other) = delete;
        single_ptr& operator = (const single_ptr& other) = delete;
        single_ptr(single_ptr&& other) noexcept {
            _ptr = other._ptr;
            _deleter = other._deleter;
            other._ptr = nullptr;
        }
        single_ptr& operator = (single_ptr&& other) noexcept {
            if (this != &other) {
                _deleter(_ptr);

                _ptr = other._ptr;
                _deleter = other._deleter;
                other._ptr = nullptr;
            }

            return *this;
        }

        ~single_ptr() {
            _deleter(_ptr);
            _ptr = nullptr;
        }

        void reset(pointer p) noexcept {
            pointer old = std::exchange(_ptr, p);
            if (old) {
                _deleter(old);
            }
        }

        pointer release() noexcept {
            return std::exchange(_ptr, pointer());
        }

        pointer get() const noexcept {
            return _ptr;
        }

        pointer operator->() const noexcept {
            return _ptr;
        }

        T& operator*() const noexcept {
            return *_ptr;
        }

    private:
        pointer _ptr = nullptr;
        Deleter _deleter;
    };
}

#endif
