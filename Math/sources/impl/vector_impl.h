#pragma once

namespace example{ namespace math{

template<typename T, std::size_t M, std::size_t N, typename Order,
         typename = typename std::enable_if<is_vector<M, N>::value>::type>
auto dot_product(const Matrix<T, M, N, Order>& lhs, const Matrix<T, M, N, Order>& rhs)
{
    using type = Matrix<T, M, N, Order>;
    typename type::value_type result = 0;
    for(typename type::size_type i = 0; i < type::size(); i++)
        result += lhs[i] * rhs[i];
    return result;
}

template<typename T, std::size_t M, std::size_t N, typename Order,
         typename = typename std::enable_if<is_n_dimensional_vector<M, N, 2>::value>::type>
typename Matrix<T, M, N, Order>::value_type cross_product(const Matrix<T, M, N, Order>& lhs, const Matrix<T, M, N, Order>& rhs)
{
    return lhs[0] * rhs[1] - lhs[1] * rhs[0];
}

template<typename T, std::size_t M, std::size_t N, typename Order,
         typename = typename std::enable_if<is_n_dimensional_vector<M, N, 3>::value>::type>
auto cross_product(const Matrix<T, M, N, Order>& lhs, const Matrix<T, M, N, Order>& rhs)
{
    using type = Matrix<T, M, N, Order>;
    type result;
    result[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
    result[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
    result[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];
    return result;
}

}}