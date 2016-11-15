#pragma once
#include <array>
#include "expression.h"

namespace mymath{

template<typename T>
class vector final
{
public:
    using type = vector<T>;
    using value_type = T;
    using size_type = size_t;
    using reference = value_type&;
    using const_reference = const value_type&;

    static constexpr size_type order_ = 2;
    using array_type = std::array<value_type, order_>;

public:
    vector() = default;
    ~vector() = default;

    explicit vector(const type& other)
    {
        array_ = other.array_;
    }

    explicit vector(const array_type& array)
    {
        array_ = array;
    }

    template<typename Exp>
    explicit vector(const Exp& expression)
    {
        for(size_type i = 0; i < order(); i++)
            array_[i] = expression[i];
    }

    type& operator = (const type& other)
    {
        array_ = other.array_;
        return *this;
    }

    template<typename Exp>
    type& operator = (const Exp& expression)
    {
        for(size_type i = 0; i < size(); i++)
            array_[i] = expression[i];
        return *this;
    }

    reference operator [] (size_type i){ return array_[i]; }
    value_type operator [] (size_type i) const { return array_[i]; }

    static constexpr size_type order(){ return order_; }
    static constexpr size_type rows(){ return order(); }
    static constexpr size_type columns(){ return 1; }
    static constexpr size_type size(){ return rows() * columns(); }

private:
    array_type array_;
};

//

template<typename L, typename Op, typename R>
class vector_expression : public expression<L, Op, R>
{
    using typename expression<L, Op, R>::l_ref_type;
    using typename expression<L, Op, R>::r_ref_type;
public:
    vector_expression(l_ref_type l, r_ref_type r)
        : expression<L, Op, R>(l, r)
    {}
};

// v_e + v_e 
template<typename L_ExpL, typename L_ExpOp, typename L_ExpR, typename R_ExpL, typename R_ExpOp, typename R_ExpR>
auto operator + (const vector_expression<L_ExpL, L_ExpOp, L_ExpR>& lhs, const vector_expression<R_ExpL, R_ExpOp, R_ExpR>& rhs)
{
    return vector_expression<vector_expression<L_ExpL, L_ExpOp, L_ExpR>, op_add, vector_expression<R_ExpL, R_ExpOp, R_ExpR>>(lhs, rhs);
}

// v + v_e
template<typename L, typename R_ExpL, typename R_ExpOp, typename R_ExpR>
auto operator + (const vector<L>& lhs, const vector_expression<R_ExpL, R_ExpOp, R_ExpR>& rhs)
{
    return vector_expression<vector<L>, op_add, vector_expression<R_ExpL, R_ExpOp, R_ExpR>>(lhs, rhs);
}

// v_e + v
template<typename L_ExpL, typename L_ExpOp, typename L_ExpR, typename R>
auto operator + (const vector_expression<L_ExpL, L_ExpOp, L_ExpR>& lhs, const vector<R>& rhs)
{
    return vector_expression<vector_expression<L_ExpL, L_ExpOp, L_ExpR>, op_add, vector<R>>(lhs, rhs);
}

// v + v
template<typename L, typename R>
auto operator + (const vector<L>& lhs, const vector<R>& rhs)
{
    return vector_expression<vector<L>, op_add, vector<R>>(lhs, rhs);
}

// v_e - v_e 
template<typename L_ExpL, typename L_ExpOp, typename L_ExpR, typename R_ExpL, typename R_ExpOp, typename R_ExpR>
auto operator - (const vector_expression<L_ExpL, L_ExpOp, L_ExpR>& lhs, const vector_expression<R_ExpL, R_ExpOp, R_ExpR>& rhs)
{
    return vector_expression<vector_expression<L_ExpL, L_ExpOp, L_ExpR>, op_subtract, vector_expression<R_ExpL, R_ExpOp, R_ExpR>>(lhs, rhs);
}

// v - v_e
template<typename L, typename R_ExpL, typename R_ExpOp, typename R_ExpR>
auto operator - (const vector<L>& lhs, const vector_expression<R_ExpL, R_ExpOp, R_ExpR>& rhs)
{
    return vector_expression<vector<L>, op_subtract, vector_expression<R_ExpL, R_ExpOp, R_ExpR>>(lhs, rhs);
}

// v_e - v
template<typename L_ExpL, typename L_ExpOp, typename L_ExpR, typename R>
auto operator - (const vector_expression<L_ExpL, L_ExpOp, L_ExpR>& lhs, const vector<R>& rhs)
{
    return vector_expression<vector_expression<L_ExpL, L_ExpOp, L_ExpR>, op_subtract, vector<R>>(lhs, rhs);
}

// v - v
template<typename L, typename R>
auto operator - (const vector<L>& lhs, const vector<R>& rhs)
{
    return vector_expression<vector<L>, op_subtract, vector<R>>(lhs, rhs);
}

// s * v_e
template<typename L, typename R_ExpL, typename R_ExpOp, typename R_ExpR, typename = typename std::enable_if<std::is_arithmetic<L>::value>::type>
auto operator * (const L& lhs, const vector_expression<R_ExpL, R_ExpOp, R_ExpR>& rhs)
{
    return vector_expression<scalar<L>, op_multiply, vector_expression<R_ExpL, R_ExpOp, R_ExpR>>(scalar<L>(lhs), rhs);
}

// s * v
template<typename L, typename R, typename = typename std::enable_if<std::is_arithmetic<L>::value>::type>
auto operator * (const L& lhs, const vector<R>& rhs)
{
    return vector_expression<scalar<L>, op_multiply, vector<R>>(scalar<L>(lhs), rhs);
}

// v_e * s
template<typename L_ExpL, typename L_ExpOp, typename L_ExpR, typename R, typename = typename std::enable_if<std::is_arithmetic<R>::value>::type>
auto operator * (const vector_expression<L_ExpL, L_ExpOp, L_ExpR>& lhs, const R& rhs)
{
    return vector_expression<vector_expression<L_ExpL, L_ExpOp, L_ExpR>, op_multiply, scalar<R>>(lhs, scalar<R>(rhs));
}

// v * s
template<typename L, typename R, typename = typename std::enable_if<std::is_arithmetic<R>::value>::type>
auto operator * (const vector<L>& lhs, const R& rhs)
{
    return vector_expression<vector<L>, op_multiply, scalar<R>>(lhs, scalar<R>(rhs));
}

// v_e / s
template<typename L_ExpL, typename L_ExpOp, typename L_ExpR, typename R, typename = typename std::enable_if<std::is_arithmetic<R>::value>::type>
auto operator / (const vector_expression<L_ExpL, L_ExpOp, L_ExpR>& lhs, const R& rhs)
{
    return vector_expression<vector_expression<L_ExpL, L_ExpOp, L_ExpR>, op_divide, scalar<R>>(lhs, scalar<R>(rhs));
}

// v / s
template<typename L, typename R, typename = typename std::enable_if<std::is_arithmetic<R>::value>::type>
auto operator / (const vector<L>& lhs, const R& rhs)
{
    return vector_expression<vector<L>, op_divide, scalar<R>>(lhs, scalar<R>(rhs));
}

// for debug
template<typename T>
std::ostream& operator << (std::ostream& os, const vector<T>& v)
{
    const auto flags = os.flags();
    os << "vector{";
    for(typename vector<T>::size_type i = 0; i < vector<T>::size(); i++){
        os << v[i] << ", ";
    }
    os << "}";
    os.flags(flags);
    return os;
}

}