#pragma once

namespace example{ namespace math{

template<typename T, std::size_t M, std::size_t N, typename Order>
class Matrix;

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

    void operator = (const Matrix<matrix_value_type, Rows, Columns, matrix_storage_order_type>& other);
    operator cast_type () const;

private:
    MatrixRefType ref_;
    matrix_size_type row_;
    matrix_size_type column_;
};

template<typename MatrixRefType, std::size_t Rows, std::size_t Columns>
void Block<MatrixRefType, Rows, Columns>::operator = (const Matrix<matrix_value_type, Rows, Columns, matrix_storage_order_type>& other)
{
    for(matrix_size_type i = 0; i < Rows; i++)
        for(matrix_size_type j = 0; j < Columns; j++)
            ref_(row_ + i, column_ + j) = other(i, j);
}

template<typename MatrixRefType, std::size_t Rows, std::size_t Columns>
Block<MatrixRefType, Rows, Columns>::operator cast_type () const
{
    cast_type result;
    for(matrix_size_type i = 0; i < Rows; i++)
        for(matrix_size_type j = 0; j < Columns; j++)
            result(i, j) = ref_(row_ + i, column_ + j);
    return result;
}

}}