#pragma once

namespace example{ namespace math{

template<typename MatrixRefType, std::size_t Rows, std::size_t Columns>
template<typename Order>
typename std::enable_if<std::is_same<Order, column_major_order>::value>::type Block<MatrixRefType, Rows, Columns>::operator = (const Matrix<matrix_value_type, Rows, Columns, matrix_storage_order_type>& other)
{
    for(matrix_size_type i = 0; i < Columns; i++)
        for(matrix_size_type j = 0; j < Rows; j++)
            ref_(row_ + j, column_ + i) = other(j, i);
}

template<typename MatrixRefType, std::size_t Rows, std::size_t Columns>
template<typename Order>
typename std::enable_if<std::is_same<Order, row_major_order>::value>::type Block<MatrixRefType, Rows, Columns>::operator = (const Matrix<matrix_value_type, Rows, Columns, matrix_storage_order_type>& other)
{
    for(matrix_size_type i = 0; i < Rows; i++)
        for(matrix_size_type j = 0; j < Columns; j++)
            ref_(row_ + i, column_ + j) = other(i, j);
}

template<typename MatrixRefType, std::size_t Rows, std::size_t Columns>
template<typename T, typename Order>
Block<MatrixRefType, Rows, Columns>::operator typename std::enable_if<std::is_same<Order, column_major_order>::value, T>::type() const
{
    cast_type result;
    for(matrix_size_type i = 0; i < Columns; i++)
        for(matrix_size_type j = 0; j < Rows; j++)
            result(j, i) = ref_(row_ + j, column_ + i);
    return result;
}

template<typename MatrixRefType, std::size_t Rows, std::size_t Columns>
template<typename T, typename Order>
Block<MatrixRefType, Rows, Columns>::operator typename std::enable_if<std::is_same<Order, row_major_order>::value, T>::type() const
{
    cast_type result;
    for(matrix_size_type i = 0; i < Rows; i++)
        for(matrix_size_type j = 0; j < Columns; j++)
            result(i, j) = ref_(row_ + i, column_ + j);
    return result;
}

}}