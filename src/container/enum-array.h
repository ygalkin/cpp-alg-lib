#ifndef _CONTAINER_ENUM_ARRAY_
#define _CONTAINER_ENUM_ARRAY_

// Enum array implementation

namespace container {

    template <typename T, std::size_t...Is>
    inline constexpr std::array<T, sizeof...(Is)> make_array(const T& value, std::index_sequence<Is...>) {
        return { {(static_cast<void>(Is), value)...} };
    }

    template <typename T, typename E>
    class enum_array {
    public:
        constexpr enum_array() = default;
        constexpr ~enum_array() = default;
        constexpr explicit enum_array(T t) :
            _array{ make_array(t, std::make_index_sequence<std::to_underlying(E::SIZE)>()) } {}

        template <E e>
        constexpr T& at() noexcept {
            _validate_static<e>();

            return _array[std::to_underlying<E>(e)];
        }

        template <E e>
        constexpr const T& at() const noexcept {
            _validate_static<e>();

            return _array[std::to_underlying<E>(e)];
        }

        T& operator[](E e) {
            _validate_dynamic(e);

            return _array[std::to_underlying<E>(e)];
        }

        const T& operator[](E e) const {
            _validate_dynamic(e);

            return _array[std::to_underlying<E>(e)];
        }

        consteval size_t size() const noexcept {
            return std::to_underlying<E>(E::SIZE);
        }

    private:
        template <E e>
        constexpr void _validate_static() const noexcept {
            static_assert(std::to_underlying<E>(e) >= 0, "Array index out of lower bound.");
            static_assert(std::to_underlying<E>(e) < std::to_underlying<E>(E::SIZE), "Array index out of upper bound.");
        }

        void _validate_dynamic(E e) const {
            if (std::to_underlying<E>(e) < 0) {
                throw std::out_of_range("Array index out of lower bound.");
            }

            if (std::to_underlying<E>(e) >= std::to_underlying<E>(E::SIZE)) {
                throw std::out_of_range("Array index out of upper bound.");
            }
        }

        std::array<T, std::to_underlying<E>(E::SIZE)> _array;
    };
}

#endif