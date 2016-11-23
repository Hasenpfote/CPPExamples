#pragma once

namespace example{ namespace math{

template<typename T, std::size_t M, std::size_t N, typename Order>
class Matrix;

template<typename T, std::size_t M, std::size_t N, std::size_t P, std::size_t Q, typename Order>
class Block final
{
    using size_type = std::size_t;
public:
    Block(Matrix<T, M, N, Order>& ref, size_type row, size_type column)
        : ref_(ref), row_(row), column_(column)
    {}

    void operator = (const Matrix<T, P, Q, Order>& other)
    {
        for (size_type i = 0; i < P; i++)
            for (size_type j = 0; j < Q; j++)
                ref_(row_ + i, column_ + j) = other(i, j);
    }
private:
    Matrix<T, M, N, Order>& ref_;
    size_type row_;
    size_type column_;
};

}}