#pragma once
#include <array>
#include <iostream>

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
struct is_column_matrix<M, N, typename std::enable_if<N == 1>::type>
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
struct is_row_matrix<M, N, typename std::enable_if<M == 1>::type>
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

// matrix
template<typename T, std::size_t M, std::size_t N = M, typename Order = column_major_order>
class matrix final
{
public:
    using type = matrix<T, M, N, Order>;
    using value_type = T;
    using size_type = std::size_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using storage_type = std::array<value_type, M * N>;

public:
    // Ctor and Dtor.
    matrix() = default;
    ~matrix() = default;

    matrix(const type& other);
    explicit matrix(const storage_type& storage);

    // Assignment operator.
    type& operator = (const type& other);

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

}}

#include "impl/matrix_impl.h"