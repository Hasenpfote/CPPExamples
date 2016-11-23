#pragma once
#include <array>
#include <iostream>
#include <cassert>

#define ENABLE_BLOCK_TEST
#if defined(ENABLE_BLOCK_TEST)
#include "block.h"
#endif

namespace example{ namespace math{

// storage_order_traits
struct column_major_order {};
struct row_major_order {};

namespace detail{

struct storage_order_tag {};
struct column_major_order_tag : storage_order_tag {};
struct row_major_order_tag : storage_order_tag {};

template<typename T>
struct storage_order_traits
{
    using storage_order_category = detail::column_major_order_tag;
};

template<>
struct storage_order_traits<row_major_order>
{
    using storage_order_category = detail::row_major_order_tag;
};

}

// is_square_matrix
template<std::size_t M, std::size_t N, typename Enable = void>
struct is_square_matrix
    : std::false_type
{
};

template<std::size_t M, std::size_t N>
struct is_square_matrix<M, N, typename std::enable_if<M == N>::type>
    : std::true_type
{
};

// is_column_matrix
template<std::size_t M, std::size_t N, typename Enable = void>
struct is_column_matrix
    : std::false_type
{
};

template<std::size_t M, std::size_t N>
struct is_column_matrix<M, N, typename std::enable_if<(M > 1) && (N == 1)>::type>
    : std::true_type
{
};

// is_row_matrix
template<std::size_t M, std::size_t N, typename Enable = void>
struct is_row_matrix
    : std::false_type
{
};

template<std::size_t M, std::size_t N>
struct is_row_matrix<M, N, typename std::enable_if<(M == 1) && (N > 1)>::type>
    : std::true_type
{
};

// is_vector
template<std::size_t M, std::size_t N, typename Enable = void>
struct is_vector
    : std::false_type
{
};

template<std::size_t M, std::size_t N>
struct is_vector<M, N,
    typename std::enable_if<is_column_matrix<M, N>::value || is_row_matrix<M, N>::value>::type>
    : std::true_type
{
};

// is_n_dimensional_vector
template<std::size_t M, std::size_t N, std::size_t D, typename Enable = void>
struct is_n_dimensional_vector
    : std::false_type
{
};

template<std::size_t M, std::size_t N, std::size_t D>
struct is_n_dimensional_vector<M, N, D,
                               typename std::enable_if<(is_column_matrix<M, N>::value && (M == D))
                                                    || (is_row_matrix<M, N>::value && (N == D))>::type>
    : std::true_type
{
};

// is_scalar
template<std::size_t M, std::size_t N, typename Enable = void>
struct is_scalar
    : std::false_type
{
};

template<std::size_t M, std::size_t N>
struct is_scalar<M, N, typename std::enable_if<(M == 1) && (N == 1)>::type>
    : std::true_type
{
};

// Matrix
template<typename T, std::size_t M, std::size_t N = M, typename Order = column_major_order>
class Matrix final
{
public:
    using type = Matrix<T, M, N, Order>;
    using value_type = T;
    using size_type = std::size_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using storage_order_type = Order;
    using storage_type = std::array<value_type, M * N>;

public:
    // Ctor and Dtor.
    Matrix() = default;
    ~Matrix() = default;

    Matrix(const type& other);
    explicit Matrix(const storage_type& storage);

    // Assignment operator.
    type& operator = (const type& other);
    type& operator += (const type& other);
    type& operator -= (const type& other);
    type& operator *= (value_type scalar);
    type& operator /= (value_type divisor);

    template<typename _Order = Order>
    typename std::enable_if<std::is_same<_Order, column_major_order>::value, Matrix<T, M, N, Order>>::type& operator *= (const Matrix<T, N, N, Order>& other);

    template<typename _Order = Order>
    typename std::enable_if<std::is_same<_Order, row_major_order>::value, Matrix<T, M, N, Order>>::type& operator *= (const Matrix<T, N, N, Order>& other);

    // Casting operator.
    explicit operator pointer ();
    explicit operator const_pointer () const;

    // Subscript operator.
    reference operator [] (size_type i);
    value_type operator [] (size_type i) const;

    reference operator () (size_type row, size_type column);
    value_type operator () (size_type row, size_type column) const;

    //
    static constexpr size_type rows();
    static constexpr size_type columns();
    static constexpr size_type size();

    static constexpr size_type index(size_type row, size_type column);
    static constexpr size_type row_subscript(size_type index);
    static constexpr size_type column_subscript(size_type index);

    //
    template<std::size_t _M = M>
    typename std::enable_if<is_square_matrix<_M, N>::value, T>::type trace() const;

#if defined(ENABLE_BLOCK_TEST)
    template<std::size_t P, std::size_t Q>
    auto block(size_type row, size_type column);

    template<std::size_t P, std::size_t Q>
    auto block(size_type row, size_type column) const;
#endif

private:
    static constexpr size_type index(size_type row, size_type column, detail::column_major_order_tag);
    static constexpr size_type index(size_type row, size_type column, detail::row_major_order_tag);

    static constexpr size_type row_subscript(size_type index, detail::column_major_order_tag);
    static constexpr size_type column_subscript(size_type index, detail::column_major_order_tag);

    static constexpr size_type row_subscript(size_type index, detail::row_major_order_tag);
    static constexpr size_type column_subscript(size_type index, detail::row_major_order_tag);

private:
    storage_type storage_;
};

#if defined(ENABLE_BLOCK_TEST)
template<typename T, std::size_t M, std::size_t N, typename Order>
template<std::size_t P, std::size_t Q>
auto Matrix<T, M, N, Order>::block(size_type row, size_type column)
{
    return Block<decltype(*this), P, Q>(*this, row, column);
}

template<typename T, std::size_t M, std::size_t N, typename Order>
template<std::size_t P, std::size_t Q>
auto Matrix<T, M, N, Order>::block(size_type row, size_type column) const
{
    return Block<decltype(*this), P, Q>(*this, row, column);
}
#endif

}}

#include "impl/matrix_impl.h"
#include "impl/vector_impl.h"