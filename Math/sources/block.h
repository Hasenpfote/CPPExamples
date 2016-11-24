#pragma once

namespace example{ namespace math{

struct column_major_order;
struct row_major_order;

template<typename T, std::size_t M, std::size_t N, typename Order>
class Matrix;

// Block
template<typename MatrixRefType, std::size_t Rows, std::size_t Columns>
class Block final
{
    using matrix_type = typename std::remove_reference<MatrixRefType>::type;
    using matrix_value_type = typename matrix_type::value_type;
    using matrix_size_type = typename matrix_type::size_type;
    using matrix_storage_order_type = typename matrix_type::storage_order_type;
    using cast_type = Matrix<matrix_value_type, Rows, Columns, matrix_storage_order_type>;
public:
    Block(MatrixRefType ref, matrix_size_type row, matrix_size_type column)
        : ref_(ref), row_(row), column_(column)
    {
    }

    // Assignment operator.
    template<typename Order = matrix_storage_order_type>
    typename std::enable_if<std::is_same<Order, column_major_order>::value>::type operator = (const Matrix<matrix_value_type, Rows, Columns, matrix_storage_order_type>& other);

    template<typename Order = matrix_storage_order_type>
    typename std::enable_if<std::is_same<Order, row_major_order>::value>::type operator = (const Matrix<matrix_value_type, Rows, Columns, matrix_storage_order_type>& other);

    // 'Implicit' Casting operator.
    template<typename T = cast_type, typename Order = matrix_storage_order_type>
    operator typename std::enable_if<std::is_same<Order, column_major_order>::value, T>::type () const;

    template<typename T = cast_type, typename Order = matrix_storage_order_type>
    operator typename std::enable_if<std::is_same<Order, row_major_order>::value, T>::type () const;

private:
    MatrixRefType ref_;
    matrix_size_type row_;
    matrix_size_type column_;
};

}}

#include "impl/block_impl.h"