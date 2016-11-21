#include <iostream>
#include <cassert>
#include "matrix.h"

using namespace example::math;

template<typename T, std::size_t M, std::size_t N, typename Order>
auto operator + (const matrix<T, M, N, Order>& lhs, const matrix<T, M, N, Order>& rhs)
{
    using type = matrix<T, M, N, Order>;
    type result;
    for(typename type::size_type i = 0; i < type::size(); i++)
        result[i] = lhs[i] + rhs[i];
    return result;
}

//column vector notation with column major order.
template<typename T, std::size_t M, std::size_t N, std::size_t P,
         typename = typename std::enable_if<!is_row_matrix<N, P>::value>::type>
auto operator * (const matrix<T, M, N, column_major_order>& lhs, const matrix<T, N, P, column_major_order>& rhs)
{
    std::cout << "column_major_order" << std::endl;

    using type = matrix<T, M, P, column_major_order>;
    type result;
    typename type::value_type elem;
    for(typename type::size_type i = 0; i < P; i++){
        for(typename type::size_type j = 0; j < M; j++){
            elem = 0;
            for(typename type::size_type k = 0; k < N; k++){
                elem += lhs(j, k) * rhs(k, i);
            }
            result(j,i) = elem;
        }
    }
    return result;
}

// row matrix notation and row major order.
template<typename T, std::size_t M, std::size_t N, std::size_t P,
         typename = typename std::enable_if<!is_column_matrix<M, N>::value>::type>
auto operator * (const matrix<T, M, N, row_major_order>& lhs, const matrix<T, N, P, row_major_order>& rhs)
{
    std::cout << "row_major_order" << std::endl;

    using type = matrix<T, M, P, row_major_order>;
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

template<typename T, std::size_t M, std::size_t N, typename Order,
         typename = typename std::enable_if<is_vector<M, N>::value>::type>
auto dot_product(const matrix<T, M, N, Order>& lhs, const matrix<T, M, N, Order>& rhs)
{
    using type = matrix<T, M, N, Order>;
    typename type::value_type result = 0;
    for(typename type::size_type i = 0; i < type::size(); i++)
        result += lhs[i] * rhs[i];
    return result;
}

template<typename T, std::size_t M, std::size_t N, typename Order,
         typename = typename std::enable_if<is_n_dimensional_vector<M, N, 2>::value>::type>
typename matrix<T, M, N, Order>::value_type cross_product(const matrix<T, M, N, Order>& lhs, const matrix<T, M, N, Order>& rhs)
{
    return lhs[0] * rhs[1] - lhs[1] * rhs[0];
}

template<typename T, std::size_t M, std::size_t N, typename Order,
         typename = typename std::enable_if<is_n_dimensional_vector<M, N, 3>::value>::type>
auto cross_product(const matrix<T, M, N, Order>& lhs, const matrix<T, M, N, Order>& rhs)
{
    using type = matrix<T, M, N, Order>;
    type result;
    result[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
    result[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
    result[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];
    return result;
}

int main()
{
    {
        constexpr auto dim = is_n_dimensional_vector<1, 3, 3>::value;
    
    }
    {
        std::cout << "=== column_major_order" << std::endl;
        using matrix = matrix<float, 2, 3, column_major_order>;
        matrix m({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f});
        for(matrix::size_type i = 0; i < matrix::size(); i++){
            auto row = matrix::row_subscript(i);
            auto col = matrix::column_subscript(i);
            std::cout << "index " << i << " => (" << row << ", " << col << ") = " << m(row, col) << std::endl;
        }
        std::cout << std::endl;
    }
    {
        std::cout << "=== row_major_order" << std::endl;
        using matrix = matrix<float, 2, 3, row_major_order>;
        matrix m({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f });
        for(matrix::size_type i = 0; i < matrix::size(); i++){
            auto row = matrix::row_subscript(i);
            auto col = matrix::column_subscript(i);
            std::cout << "index " << i << " => (" << row << ", " << col << ") = " << m(row, col) << std::endl;
        }
        std::cout << std::endl;
    }

    {
        using matrix = matrix<float, 2, 2, column_major_order>;
        //using matrix = matrix<float, 2, 2, row_major_order>;
        matrix ma({ 1.0f, 2.0f, 3.0f, 4.0f });
        matrix mb({ 1.0f, 2.0f, 3.0f, 4.0f });
        matrix mc;

        auto val11 = ma(0, 0);
        auto val12 = ma(0, 1);
        auto val21 = ma(1, 0);
        auto val22 = ma(1, 1);

        //mc = ma + mb;
        //std::cout << mc << std::endl;
        mc = ma * mb;
        std::cout << mc << std::endl;
    }
    {
        //using vector = matrix<float, 1, 2, row_major_order>;
        //using matrix = matrix<float, 2, 2, row_major_order>;
        using vector = matrix<float, 2, 1, column_major_order>;
        using matrix = matrix<float, 2, 2, column_major_order>;

        vector va({ 1.0f, 2.0f });
        matrix m({ 1.0f, 2.0f, 3.0f, 4.0f });
        vector v;
        v = m * va;
        //v = va * m;
        std::cout << v << std::endl;
    }
    {
        //using vector = matrix<float, 1, 2>;
        using vector = matrix<float, 2, 1>;
        vector a({ 1.0f, 2.0f });
        vector b({ 2.0f, 3.0f });
        auto dot = dot_product(a, b);
        std::cout << dot << std::endl;
    }
    {
        using vector = matrix<float, 1, 2>;
        vector a({ 1.0f, 2.0f });
        vector b({ 4.0f, 5.0f });
        auto cross = cross_product(a, b);
    }
    {
        using vector = matrix<float, 3, 1>;
        vector a({ 1.0f, 2.0f, 3.0f });
        vector b({ 4.0f, 5.0f, 6.0f });
        auto cross = cross_product(a, b);
    }
    return 0;
}
