#pragma once
#include <array>
#include <iostream>

namespace example{ namespace math{

// storage_order_traits
struct storage_order_tag {};
struct column_major_order_tag : storage_order_tag {};
struct row_major_order_tag : storage_order_tag {};

struct column_major_order {};
struct row_major_order {};

template<typename T>
struct storage_order_traits
{
    using storage_order_category = column_major_order_tag;
};

template<>
struct storage_order_traits<row_major_order>
{
    using storage_order_category = row_major_order_tag;
};

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

    matrix(const type& other){ storage_ = other.storage_; }
    explicit matrix(const storage_type& storage){ storage_ = storage; }

    // Assignment operator.
    type& operator = (const type& other){ storage_ = other.storage_; return *this; }

    // Casting operator.
    explicit operator pointer (){ return storage_.data(); }
    explicit operator const_pointer () const { return storage_.data(); }

    // Subscript operator.
    reference operator [] (size_type i){ return storage_[i]; }
    value_type operator [] (size_type i) const { return storage_[i]; }

    reference operator () (size_type row, size_type column){ return storage_[index(row, column)]; }
    value_type operator () (size_type row, size_type column) const { return storage_[index(row, column)]; }

    //
    static constexpr size_type rows(){ return M; }
    static constexpr size_type columns(){ return N; }
    static constexpr size_type size(){ return rows() * columns(); }

    static constexpr size_type index(size_type row, size_type column)
    {
        return index(row, column, typename storage_order_traits<Order>::storage_order_category());
    }

    static constexpr size_type row_subscript(size_type index)
    {
        return row_subscript(index, typename storage_order_traits<Order>::storage_order_category());
    }

    static constexpr size_type column_subscript(size_type index)
    {
        return column_subscript(index, typename storage_order_traits<Order>::storage_order_category());
    }

private:
    static constexpr size_type index(size_type row, size_type column, column_major_order_tag){ return column * rows() + row; }
    static constexpr size_type index(size_type row, size_type column, row_major_order_tag){ return row * columns() + column; }

    static constexpr size_type row_subscript(size_type index, column_major_order_tag){ return index % rows(); }
    static constexpr size_type column_subscript(size_type index, column_major_order_tag){ return index / rows(); }

    static constexpr size_type row_subscript(size_type index, row_major_order_tag){ return index / columns(); }
    static constexpr size_type column_subscript(size_type index, row_major_order_tag){ return index % columns(); }

private:
    storage_type storage_;
};

// for debug
template<typename T, std::size_t M, std::size_t N, typename Order>
std::ostream& operator << (std::ostream& os, const matrix<T, M, N, Order>& m)
{
    using type = matrix<T, M, N, Order>;
    const auto flags = os.flags();
    for(typename type::size_type i = 0; i < type::rows(); i++){
        os << "matrix(" << i << "){" << m(i, 0);
        for(typename type::size_type j = 1; j < type::columns(); j++){
            os << ", " << m(i, j);
        }
        os << "}" << std::endl;
    }
    os.flags(flags);
    return os;
}

}}