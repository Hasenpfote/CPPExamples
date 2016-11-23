#pragma once

namespace example{ namespace math{

// Ctor and Dtor.
template<typename T, std::size_t M, std::size_t N, typename Order>
Matrix<T, M, N, Order>::Matrix(const type& other)
{
    storage_ = other.storage_;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
Matrix<T, M, N, Order>::Matrix(const storage_type& storage)
{
    storage_ = storage;
}

// Assignment operator.
template<typename T, std::size_t M, std::size_t N, typename Order>
typename Matrix<T, M, N, Order>::type& Matrix<T, M, N, Order>::operator = (const type & other)
{
    storage_ = other.storage_;
    return *this;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
typename Matrix<T, M, N, Order>::type& Matrix<T, M, N, Order>::operator += (const type& other)
{
    for(typename Matrix::size_type i = 0; i < size(); i++)
        storage_[i] += other[i];
    return *this;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
typename Matrix<T, M, N, Order>::type& Matrix<T, M, N, Order>::operator -= (const type& other)
{
    for(typename Matrix::size_type i = 0; i < size(); i++)
        storage_[i] -= other[i];
    return *this;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
typename Matrix<T, M, N, Order>::type& Matrix<T, M, N, Order>::operator *= (value_type scalar)
{
    for(typename Matrix::size_type i = 0; i < size(); i++)
        storage_[i] *= scalar;
    return *this;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
typename Matrix<T, M, N, Order>::type& Matrix<T, M, N, Order>::operator /= (value_type divisor)
{
    for(typename Matrix::size_type i = 0; i < size(); i++)
        storage_[i] /= divisor;
    return *this;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
template<typename _Order>
typename std::enable_if<std::is_same<_Order, column_major_order>::value, Matrix<T, M, N, Order>>::type& Matrix<T, M, N, Order>::operator *= (const Matrix<T, N, N, Order>& other)
{
    Matrix temp(*this);
    typename Matrix::value_type elem;
    for(typename Matrix::size_type i = 0; i < N; i++){
        for(typename Matrix::size_type j = 0; j < M; j++){
            elem = 0;
            for(typename Matrix::size_type k = 0; k < N; k++){
                elem += temp(j, k) * other(k, i);
            }
            (*this)(j,i) = elem;
        }
    }
    return *this;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
template<typename _Order>
typename std::enable_if<std::is_same<_Order, row_major_order>::value, Matrix<T, M, N, Order>>::type& Matrix<T, M, N, Order>::operator *= (const Matrix<T, N, N, Order>& other)
{
    Matrix temp(*this);
    typename Matrix::value_type elem;
    for(typename Matrix::size_type i = 0; i < M; i++){
        for(typename Matrix::size_type j = 0; j < N; j++){
            elem = 0;
            for(typename Matrix::size_type k = 0; k < N; k++){
                elem += temp(i, k) * other(k, j);
            }
            (*this)(i, j) = elem;
        }
    }
    return *this;
}

// Casting operator.
template<typename T, std::size_t M, std::size_t N, typename Order>
Matrix<T, M, N, Order>::operator pointer ()
{
    return storage_.data();
}

template<typename T, std::size_t M, std::size_t N, typename Order>
Matrix<T, M, N, Order>::operator const_pointer () const
{
    return storage_.data();
}

// Subscript operator.
template<typename T, std::size_t M, std::size_t N, typename Order>
typename Matrix<T, M, N, Order>::reference Matrix<T, M, N, Order>::operator [] (size_type i)
{
    return storage_[i];
}

template<typename T, std::size_t M, std::size_t N, typename Order>
typename Matrix<T, M, N, Order>::value_type Matrix<T, M, N, Order>::operator [] (size_type i) const
{
    return storage_[i];
}

template<typename T, std::size_t M, std::size_t N, typename Order>
typename Matrix<T, M, N, Order>::reference Matrix<T, M, N, Order>::operator () (size_type row, size_type column)
{
    return storage_[index(row, column)];
}

template<typename T, std::size_t M, std::size_t N, typename Order>
typename Matrix<T, M, N, Order>::value_type Matrix<T, M, N, Order>::operator () (size_type row, size_type column) const
{
    return storage_[index(row, column)];
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename Matrix<T, M, N, Order>::size_type Matrix<T, M, N, Order>::rows()
{
    return M;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename Matrix<T, M, N, Order>::size_type Matrix<T, M, N, Order>::columns()
{
    return N;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename Matrix<T, M, N, Order>::size_type Matrix<T, M, N, Order>::size()
{
    return rows() * columns();
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename Matrix<T, M, N, Order>::size_type Matrix<T, M, N, Order>::index(size_type row, size_type column)
{
    return index(row, column, typename detail::storage_order_traits<Order>::storage_order_category());
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename Matrix<T, M, N, Order>::size_type Matrix<T, M, N, Order>::row_subscript(size_type index)
{
    return row_subscript(index, typename detail::storage_order_traits<Order>::storage_order_category());
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename Matrix<T, M, N, Order>::size_type Matrix<T, M, N, Order>::column_subscript(size_type index)
{
    return column_subscript(index, typename detail::storage_order_traits<Order>::storage_order_category());
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename Matrix<T, M, N, Order>::size_type Matrix<T, M, N, Order>::index(size_type row, size_type column, detail::column_major_order_tag)
{
    return column * rows() + row;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename Matrix<T, M, N, Order>::size_type Matrix<T, M, N, Order>::index(size_type row, size_type column, detail::row_major_order_tag)
{
    return row * columns() + column;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename Matrix<T, M, N, Order>::size_type Matrix<T, M, N, Order>::row_subscript(size_type index, detail::column_major_order_tag)
{
    return index % rows();
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename Matrix<T, M, N, Order>::size_type Matrix<T, M, N, Order>::column_subscript(size_type index, detail::column_major_order_tag)
{
    return index / rows();
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename Matrix<T, M, N, Order>::size_type Matrix<T, M, N, Order>::row_subscript(size_type index, detail::row_major_order_tag)
{
    return index / columns();
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename Matrix<T, M, N, Order>::size_type Matrix<T, M, N, Order>::column_subscript(size_type index, detail::row_major_order_tag)
{
    return index % columns();
}

//
template<typename T, std::size_t M, std::size_t N, typename Order>
template<std::size_t _M>
typename std::enable_if<is_square_matrix<_M, N>::value, T>::type Matrix<T, M, N, Order>::trace() const
{
    typename Matrix::value_type result = 0;
    for(typename Matrix::size_type i = 0; i < M; i++)
        result += (*this)(i, i);
    return result;
}

// Unary operator.

// Binary operator.
template<typename T, std::size_t M, std::size_t N, typename Order>
auto operator + (const Matrix<T, M, N, Order>& lhs, const Matrix<T, M, N, Order>& rhs)
{
    return Matrix<T, M, N, Order>(lhs) += rhs;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
auto operator - (const Matrix<T, M, N, Order>& lhs, const Matrix<T, M, N, Order>& rhs)
{
    return Matrix<T, M, N, Order>(lhs) -= rhs;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
auto operator * (const Matrix<T, M, N, Order>& lhs, typename Matrix<T, M, N, Order>::value_type rhs)
{
    return Matrix<T, M, N, Order>(lhs) *= rhs;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
auto operator * (typename Matrix<T, M, N, Order>::value_type lhs, const Matrix<T, M, N, Order>& rhs)
{
    return Matrix<T, M, N, Order>(rhs) *= lhs;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
auto operator / (const Matrix<T, M, N, Order>& lhs, typename Matrix<T, M, N, Order>::value_type rhs)
{
    return Matrix<T, M, N, Order>(lhs) /= rhs;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
Matrix<T, M, N, Order> operator * (const Matrix<T, M, N, Order>& lhs, const Matrix<T, N, N, Order>& rhs)
{
    return Matrix<T, M, N, Order>(lhs) *= rhs;
}

// Column matrix notation with column major order.
template<typename T, std::size_t M, std::size_t N, std::size_t P,
         typename = typename std::enable_if<(N != P) && !is_row_matrix<N, P>::value>::type>
auto operator * (const Matrix<T, M, N, column_major_order>& lhs, const Matrix<T, N, P, column_major_order>& rhs)
{
    using type = Matrix<T, M, P, column_major_order>;
    type result;
    typename type::value_type elem;
    for(typename type::size_type i = 0; i < P; i++){
        for(typename type::size_type j = 0; j < M; j++){
            elem = 0;
            for(typename type::size_type k = 0; k < N; k++){
                elem += lhs(j, k) * rhs(k, i);
            }
            result(j, i) = elem;
        }
    }
    return result;
}

// Row matrix notation and row major order.
template<typename T, std::size_t M, std::size_t N, std::size_t P,
         typename = typename std::enable_if<(N != P) && !is_column_matrix<M, N>::value>::type>
auto operator * (const Matrix<T, M, N, row_major_order>& lhs, const Matrix<T, N, P, row_major_order>& rhs)
{
    using type = Matrix<T, M, P, row_major_order>;
    type result;
    typename type::value_type elem;
    for(typename type::size_type i = 0; i < M; i++){
        for(typename type::size_type j = 0; j < P; j++){
            elem = 0;
            for(typename type::size_type k = 0; k < N; k++){
                elem += lhs(i, k) * rhs(k, j);
            }
            result(i, j) = elem;
        }
    }
    return result;
}

// Stream out.
template<typename T, std::size_t M, std::size_t N, typename Order>
std::ostream& operator << (std::ostream& os, const Matrix<T, M, N, Order>& m)
{
    using type = Matrix<T, M, N, Order>;
    const auto flags = os.flags();
    for(typename type::size_type i = 0; i < type::rows(); i++){
        os << "Matrix(" << i << "){" << m(i, 0);
        for(typename type::size_type j = 1; j < type::columns(); j++){
            os << ", " << m(i, j);
        }
        os << "}" << std::endl;
    }
    os.flags(flags);
    return os;
}

}}