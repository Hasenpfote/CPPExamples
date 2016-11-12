#pragma once
#include <array>
#include "expression.h"

namespace mymath{

template<typename T>
class vector2 final
{
    static constexpr auto N = 2;
public:
    using type = scalar<T>;
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;

public:
    vector2() = default;
    ~vector2() = default;

    explicit vector2(const_reference other)
    {
        array = other.array;
    }

    template<typename E>
    explicit vector2(const E& expression)
    {
        for(auto i = 0; i < N; i++)
            array[i] = expression[i];
    }

    vector2(value_type x, value_type y)
    {
        array[0] = x;
        array[1] = y;
    }

    reference operator = (const_reference other)
    {
        array = other.array;
        return *this;
    }

    template<typename E>
    vector2& operator = (const E& expression)
    {
        for(auto i = 0; i < N; i++)
            array[i] = expression[i];
        return *this;
    }

    reference operator [] (std::size_t i){ return array[i]; }
    value_type operator [] (std::size_t i) const { return array[i]; }

    reference x(){ return array[0]; }
    value_type x() const { return array[0]; }
    reference y(){ return array[1]; }
    value_type y() const { return array[1]; }

private:
    std::array<value_type, N> array;
};

template<typename T>
std::ostream& operator << (std::ostream& os, const vector2<T>& v)
{
    const auto flags = os.flags();
    os << "Vector2{" << v.x() << ", " << v.y() << "}";
    os.flags(flags);
    return os;
}

}