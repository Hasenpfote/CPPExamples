#pragma once
#include <array>
#include "expression.h"

namespace mymath{

template<typename T>
class matrix final
{
public:
    using type = matrix<T>;
    using value_type = T;
    using size_type = size_t;
    using reference = value_type&;
    using const_reference = const value_type&;

    static constexpr size_type order_ = 2;
    using array_type = std::array<value_type, order_ * order_>;

public:
    matrix() = default;
    ~matrix() = default;

    explicit matrix(const type& other)
    {
        array_ = other.array_;
    }

    explicit matrix(const array_type& array)
    {
        array_ = array;
    }

    template<typename L, typename Op, typename R>
    explicit matrix(const expression<L, Op, R>& exp)
    {
        for(size_type i = 0; i < size(); i++)
            array_[i] = exp[i];
    }

    type& operator = (const type& other)
    {
        array_ = other.array_;
        return *this;
    }

    template<typename L, typename Op, typename R>
    type& operator = (const expression<L, Op, R>& exp)
    {
        for(size_type i = 0; i < size(); i++)
            array_[i] = exp[i];
        return *this;
    }

    reference operator [] (size_type i){ return array_[i]; }
    value_type operator [] (size_type i) const { return array_[i]; }

    static constexpr size_type order(){ return order_; }
    static constexpr size_type rows(){ return order(); }
    static constexpr size_type columns(){ return order(); }
    static constexpr size_type size(){ return rows() * columns(); }
    static constexpr size_type index(size_type row, size_type column) { return column * rows() + row; }

private:
    array_type array_;
};

//

template<typename L, typename Op, typename R>
class matrix_expression : public expression<L, Op, R>
{
    using typename expression<L, Op, R>::l_ref_type;
    using typename expression<L, Op, R>::r_ref_type;
public:
    matrix_expression(l_ref_type l, r_ref_type r)
        : expression<L, Op, R>(l, r)
    {}
};

// m_e + m_e 
template<typename L_ExpL, typename L_ExpOp, typename L_ExpR, typename R_ExpL, typename R_ExpOp, typename R_ExpR>
auto operator + (const matrix_expression<L_ExpL, L_ExpOp, L_ExpR>& lhs, const matrix_expression<R_ExpL, R_ExpOp, R_ExpR>& rhs)
{
    return matrix_expression<matrix_expression<L_ExpL, L_ExpOp, L_ExpR>, op_add, matrix_expression<R_ExpL, R_ExpOp, R_ExpR>>(lhs, rhs);
}

// m + m_e
template<typename L, typename R_ExpL, typename R_ExpOp, typename R_ExpR>
auto operator + (const matrix<L>& lhs, const matrix_expression<R_ExpL, R_ExpOp, R_ExpR>& rhs)
{
    return matrix_expression<matrix<L>, op_add, matrix_expression<R_ExpL, R_ExpOp, R_ExpR>>(lhs, rhs);
}

// m_e + m
template<typename L_ExpL, typename L_ExpOp, typename L_ExpR, typename R>
auto operator + (const matrix_expression<L_ExpL, L_ExpOp, L_ExpR>& lhs, const matrix<R>& rhs)
{
    return matrix_expression<matrix_expression<L_ExpL, L_ExpOp, L_ExpR>, op_add, matrix<R>>(lhs, rhs);
}

// m + m
template<typename L, typename R>
auto operator + (const matrix<L>& lhs, const matrix<R>& rhs)
{
    return matrix_expression<matrix<L>, op_add, matrix<R>>(lhs, rhs);
}

// m_e - m_e 
template<typename L_ExpL, typename L_ExpOp, typename L_ExpR, typename R_ExpL, typename R_ExpOp, typename R_ExpR>
auto operator - (const matrix_expression<L_ExpL, L_ExpOp, L_ExpR>& lhs, const matrix_expression<R_ExpL, R_ExpOp, R_ExpR>& rhs)
{
    return matrix_expression<matrix_expression<L_ExpL, L_ExpOp, L_ExpR>, op_subtract, matrix_expression<R_ExpL, R_ExpOp, R_ExpR>>(lhs, rhs);
}

// m - m_e
template<typename L, typename R_ExpL, typename R_ExpOp, typename R_ExpR>
auto operator - (const matrix<L>& lhs, const matrix_expression<R_ExpL, R_ExpOp, R_ExpR>& rhs)
{
    return matrix_expression<matrix<L>, op_subtract, matrix_expression<R_ExpL, R_ExpOp, R_ExpR>>(lhs, rhs);
}

// m_e - m
template<typename L_ExpL, typename L_ExpOp, typename L_ExpR, typename R>
auto operator - (const matrix_expression<L_ExpL, L_ExpOp, L_ExpR>& lhs, const matrix<R>& rhs)
{
    return matrix_expression<matrix_expression<L_ExpL, L_ExpOp, L_ExpR>, op_subtract, matrix<R>>(lhs, rhs);
}

// m - m
template<typename L, typename R>
auto operator - (const matrix<L>& lhs, const matrix<R>& rhs)
{
    return matrix_expression<matrix<L>, op_subtract, matrix<R>>(lhs, rhs);
}

// s * m_e
template<typename L, typename R_ExpL, typename R_ExpOp, typename R_ExpR, typename = typename std::enable_if<std::is_arithmetic<L>::value>::type>
auto operator * (const L& lhs, const matrix_expression<R_ExpL, R_ExpOp, R_ExpR>& rhs)
{
    return matrix_expression<scalar<L>, op_multiply, matrix_expression<R_ExpL, R_ExpOp, R_ExpR>>(scalar<L>(lhs), rhs);
}

// s * m
template<typename L, typename R, typename = typename std::enable_if<std::is_arithmetic<L>::value>::type>
auto operator * (const L& lhs, const matrix<R>& rhs)
{
    return matrix_expression<scalar<L>, op_multiply, matrix<R>>(scalar<L>(lhs), rhs);
}

// m_e * s
template<typename L_ExpL, typename L_ExpOp, typename L_ExpR, typename R, typename = typename std::enable_if<std::is_arithmetic<R>::value>::type>
auto operator * (const matrix_expression<L_ExpL, L_ExpOp, L_ExpR>& lhs, const R& rhs)
{
    return matrix_expression<matrix_expression<L_ExpL, L_ExpOp, L_ExpR>, op_multiply, scalar<R>>(lhs, scalar<R>(rhs));
}

// m * s
template<typename L, typename R, typename = typename std::enable_if<std::is_arithmetic<R>::value>::type>
auto operator * (const matrix<L>& lhs, const R& rhs)
{
    return matrix_expression<matrix<L>, op_multiply, scalar<R>>(lhs, scalar<R>(rhs));
}

// m_e / s
template<typename L_ExpL, typename L_ExpOp, typename L_ExpR, typename R, typename = typename std::enable_if<std::is_arithmetic<R>::value>::type>
auto operator / (const matrix_expression<L_ExpL, L_ExpOp, L_ExpR>& lhs, const R& rhs)
{
    return matrix_expression<matrix_expression<L_ExpL, L_ExpOp, L_ExpR>, op_divide, scalar<R>>(lhs, scalar<R>(rhs));
}

// m / s
template<typename L, typename R, typename = typename std::enable_if<std::is_arithmetic<R>::value>::type>
auto operator / (const matrix<L>& lhs, const R& rhs)
{
    return matrix_expression<matrix<L>, op_divide, scalar<R>>(lhs, scalar<R>(rhs));
}

// for debug
template<typename T>
std::ostream& operator << (std::ostream& os, const matrix<T>& m)
{
    const auto flags = os.flags();
    for(typename matrix<T>::size_type i = 0; i < matrix<T>::rows(); i++){
        os << "matrix[" << i << "]{" << m[matrix<T>::index(i, 0)];
        for(typename matrix<T>::size_type j = 1; j < matrix<T>::columns(); j++){
            os << ", " << m[matrix<T>::index(i, j)];
        }
        os << "}" << std::endl;
    }
    os.flags(flags);
    return os;
}

}