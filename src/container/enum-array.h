#ifndef _CONTAINER_ENUM_ARRAY_
#define _CONTAINER_ENUM_ARRAY_

// Enum array implementation

namespace container {

    template <typename T, typename E>
    class enum_array {
    public:
        // TODO

    private:
        std::array<T, E::SIZE> _array;
    };
}

#endif