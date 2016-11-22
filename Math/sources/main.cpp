#include <iostream>
#include <cassert>
#include "matrix.h"

using namespace example::math;

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

        mc = ma + mb;
        mc = ma / 2.0f;
        mc = ma * 2.0f;
        mc = 2.0f * ma;
        mc = 2.0f * ma * 3.0f;

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
    {
        using rmatrix = matrix<float, 2, 2, row_major_order>;
        using cmatrix = matrix<float, 2, 2, column_major_order>;

        rmatrix ra;
        rmatrix rb;
        ra *= rb;
        ra = ra * rb;
        ra += rb;

        cmatrix ca;
        cmatrix cb;
        ca *= cb;
        ca = ca * cb;
        ca += cb;
    }
    {
        //using matrix = matrix<float, 2, 2, row_major_order>;
        using matrix = matrix<float, 2, 2, column_major_order>;
        matrix m({ 1.0f, 2.0f, 3.0f, 4.0f });
        auto ret = m.trace();
        std::cout << ret << std::endl;
    }
    return 0;
}
