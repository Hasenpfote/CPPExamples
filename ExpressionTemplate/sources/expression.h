#pragma once
#include <cinttypes>

namespace mymath{

template<typename T>
class scalar;

template<typename E, typename T = void>
struct expression_traits
{
    using ref_type = E;
};

template<typename T>
struct expression_traits<scalar<T>, T>
{
    using ref_type = scalar<T>;
};

template<template<typename> class A, typename T>
struct expression_traits<A<T>, T>
{
    using ref_type = const A<T>&;
};

template<typename L, typename Op, typename R>
class expression
{
public:
    using value_type = void;

private:
    using l_ref_type = typename expression_traits<L, typename L::value_type>::ref_type;
    using r_ref_type = typename expression_traits<R, typename R::value_type>::ref_type;

public:
    expression(const L& l, const R& r)
        : l_(l), r_(r)
    {}

    auto operator [] (std::size_t i) const
    {
        return Op::evaluate(l_[i], r_[i]);
    }

private:
    l_ref_type l_;
    r_ref_type r_;
};

//
struct op_add final
{
    template<typename T>
    static T evaluate(T lhs, T rhs){ return static_cast<T>(lhs + rhs); }

    template<typename L, typename R>
    static auto evaluate(L lhs, R rhs){ return lhs + rhs; }
};
#if 0
template<typename L, typename R>
auto operator + (const L& lhs, const R& rhs)
{
    return expression<L, op_add, R>(lhs, rhs);
}
#endif
//
struct op_subtract final
{
    template<typename T>
    static T evaluate(T lhs, T rhs){ return static_cast<T>(lhs - rhs); }

    template<typename L, typename R>
    static auto evaluate(L lhs, R rhs){ return lhs - rhs; }
};
#if 0
template<typename L, typename R>
auto operator - (const L& lhs, const R& rhs)
{
    return expression<L, op_subtract, R>(lhs, rhs);
}
#endif
//
struct op_multiply final
{
    template<typename T>
    static T evaluate(T lhs, T rhs){ return static_cast<T>(lhs * rhs); }

    template<typename L, typename R>
    static auto evaluate(L lhs, R rhs){ return lhs * rhs; }
};
#if 0
template<typename L, typename R, class = typename std::enable_if<std::is_arithmetic<R>::value>::type>
expression<L, op_multiply, scalar<R>> operator * (const L& lhs, const R& rhs)
{
    return expression<L, op_multiply, scalar<R>>(lhs, scalar<R>(rhs));
}

template<typename L, typename R, class = typename std::enable_if<std::is_arithmetic<L>::value>::type>
expression<scalar<L>, op_multiply, R> operator * (const L& lhs, const R& rhs)
{
    return expression<scalar<L>, op_multiply, R>(scalar<L>(lhs), rhs);
}
#endif
//
struct op_divide final
{
    template<typename T>
    static T evaluate(T lhs, T rhs){ return static_cast<T>(lhs / rhs); }

    template<typename L, typename R>
    static auto evaluate(L lhs, R rhs){ return lhs / rhs; }
};
#if 0
template<typename L, typename R, class = typename std::enable_if<std::is_arithmetic<R>::value>::type>
auto operator / (const L& lhs, const R& rhs)
{
    return expression<L, op_divide, scalar<R>>(lhs, scalar<R>(rhs));
}
#endif
//
template<typename T>
class scalar final
{
public:
    using type = scalar<T>;
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;

public:
    explicit scalar(value_type value)
        : value_(value)
    {
    }

    value_type operator [] (std::size_t) const { return value_; }

private:
    value_type value_;
};

}