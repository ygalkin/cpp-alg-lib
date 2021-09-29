#ifndef _SMART_PTR_SINGLE_PTR_
#define _SMART_PTR_SINGLE_PTR_

#include <functional>
#include <memory>

// Smart pointer that owns and manages another object and supports custom deleter

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
        single_ptr(T* ptr) noexcept : _pair{ default_deleter<T>(), ptr } {}
        single_ptr(T* ptr, Deleter d) noexcept : _pair{ d, ptr } {}
        single_ptr(const single_ptr& other) = delete;
        single_ptr& operator = (const single_ptr& other) = delete;

        single_ptr(single_ptr&& other) noexcept :
            _pair{ std::forward<Deleter>(other.get_deleter()), other.release() } {}

        single_ptr& operator = (single_ptr&& other) {
            if (this != &other) {
                reset(other.release());
                _pair.first = std::forward<Deleter>(other._pair.first);
            }
            return *this;
        }

        ~single_ptr() {
            _pair.first(_pair.second);
        }

        Deleter& get_deleter() {
            return _pair.first;
        }

        void reset(pointer p) {
            pointer old = std::exchange(_pair.second, p);
            if (old) {
                _pair.first(old);
            }
        }

        pointer release() {
            return std::exchange(_pair.second, pointer());
        }

        pointer get() const noexcept {
            return _pair.second;
        }

        pointer operator->() const noexcept {
            return _pair.second;
        }

        T& operator*() const noexcept {
            return *_pair.second;
        }

    private:
        std::pair<Deleter, pointer> _pair;
    };
}

static_assert(std::is_copy_constructible<smart_ptr::single_ptr<int>>::value == false, "Shouldn't be copy constructible");
static_assert(std::is_move_constructible<smart_ptr::single_ptr<int>>::value == true, "Should be move constructible");
static_assert(std::is_copy_assignable<smart_ptr::single_ptr<int>>::value == false, "Shouldn't be copy assignable");
static_assert(std::is_move_assignable<smart_ptr::single_ptr<int>>::value == true, "Should be move assignable");

#endif
