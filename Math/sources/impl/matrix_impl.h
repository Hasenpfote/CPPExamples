#pragma once

namespace example{ namespace math{

template<typename T, std::size_t M, std::size_t N, typename Order>
matrix<T, M, N, Order>::matrix(const type& other)
{
    storage_ = other.storage_;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
matrix<T, M, N, Order>::matrix(const storage_type& storage)
{
    storage_ = storage;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
typename matrix<T, M, N, Order>::type& matrix<T, M, N, Order>::operator=(const type & other)
{
    storage_ = other.storage_;
    return *this;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
matrix<T, M, N, Order>::operator pointer ()
{
    return storage_.data();
}

template<typename T, std::size_t M, std::size_t N, typename Order>
matrix<T, M, N, Order>::operator const_pointer () const
{
    return storage_.data();
}

template<typename T, std::size_t M, std::size_t N, typename Order>
typename matrix<T, M, N, Order>::reference matrix<T, M, N, Order>::operator [] (size_type i)
{
    return storage_[i];
}

template<typename T, std::size_t M, std::size_t N, typename Order>
typename matrix<T, M, N, Order>::value_type matrix<T, M, N, Order>::operator [] (size_type i) const
{
    return storage_[i];
}

template<typename T, std::size_t M, std::size_t N, typename Order>
typename matrix<T, M, N, Order>::reference matrix<T, M, N, Order>::operator () (size_type row, size_type column)
{
    return storage_[index(row, column)];
}

template<typename T, std::size_t M, std::size_t N, typename Order>
typename matrix<T, M, N, Order>::value_type matrix<T, M, N, Order>::operator () (size_type row, size_type column) const
{
    return storage_[index(row, column)];
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename matrix<T, M, N, Order>::size_type matrix<T, M, N, Order>::rows()
{
    return M;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename matrix<T, M, N, Order>::size_type matrix<T, M, N, Order>::columns()
{
    return N;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename matrix<T, M, N, Order>::size_type matrix<T, M, N, Order>::size()
{
    return rows() * columns();
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename matrix<T, M, N, Order>::size_type matrix<T, M, N, Order>::index(size_type row, size_type column)
{
    return index(row, column, typename detail::storage_order_traits<Order>::storage_order_category());
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename matrix<T, M, N, Order>::size_type matrix<T, M, N, Order>::row_subscript(size_type index)
{
    return row_subscript(index, typename detail::storage_order_traits<Order>::storage_order_category());
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename matrix<T, M, N, Order>::size_type matrix<T, M, N, Order>::column_subscript(size_type index)
{
    return column_subscript(index, typename detail::storage_order_traits<Order>::storage_order_category());
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename matrix<T, M, N, Order>::size_type matrix<T, M, N, Order>::index(size_type row, size_type column, detail::column_major_order_tag)
{
    return column * rows() + row;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename matrix<T, M, N, Order>::size_type matrix<T, M, N, Order>::index(size_type row, size_type column, detail::row_major_order_tag)
{
    return row * columns() + column;
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename matrix<T, M, N, Order>::size_type matrix<T, M, N, Order>::row_subscript(size_type index, detail::column_major_order_tag)
{
    return index % rows();
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename matrix<T, M, N, Order>::size_type matrix<T, M, N, Order>::column_subscript(size_type index, detail::column_major_order_tag)
{
    return index / rows();
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename matrix<T, M, N, Order>::size_type matrix<T, M, N, Order>::row_subscript(size_type index, detail::row_major_order_tag)
{
    return index / columns();
}

template<typename T, std::size_t M, std::size_t N, typename Order>
constexpr typename matrix<T, M, N, Order>::size_type matrix<T, M, N, Order>::column_subscript(size_type index, detail::row_major_order_tag)
{
    return index % columns();
}


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