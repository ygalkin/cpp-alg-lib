#pragma once

namespace smart_ptr {

    // deleter
    template <typename T>
    struct default_deleter {
        void operator() (T* p) {
            delete p;
        }
    };

    template <typename T, typename Deleter = default_deleter<T>>
    class single_ptr {
    public:
        single_ptr() = delete;
        single_ptr(T* ptr) noexcept : _ptr{ ptr } {
        }
        // non copy constructible
        single_ptr(const single_ptr& other) = delete;
        // non copy assignable
        single_ptr& operator = (const single_ptr& other) = delete;
        // movable
        single_ptr(single_ptr&& other) noexcept {
            _ptr = other._ptr;
            other._ptr = nullptr;
        }
        // move assignment
        single_ptr& operator = (single_ptr&& other) noexcept {
            if (this != &other) {
                Deleter d;
                d(_ptr);

                _ptr = other._ptr;
                other._ptr = nullptr;
            }

            return *this;
        }

        ~single_ptr() {
            Deleter d;
            d(_ptr);
            _ptr = nullptr;
        }

        void reset(T* p) noexcept {
            T* old_ptr = _ptr;
            _ptr = p;
            Deleter d;
            d(old_ptr);
        }

        T* release() noexcept {
            auto old_ptr = _ptr;
            _ptr = nullptr;
            return old_ptr;
        }

        T* get() const noexcept {
            return _ptr;
        }

        T* operator -> () const noexcept {
            return _ptr;
        }

        T& operator * () const noexcept {
            return *_ptr;
        }

    private:
        T* _ptr = nullptr;
    };
}
