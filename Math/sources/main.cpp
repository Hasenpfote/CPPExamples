#include <iostream>
#include <cassert>
#include <typeinfo>
#include "matrix.h"

using namespace example::math;


template<typename T1, typename T2>
struct traits
{
    typedef typename std::conditional<std::is_const<T1>::value,
        typename std::add_const<T2>::type,
        typename std::remove_const<T2>::type>::type type;
};

template<typename BarRef>
struct foo
{
    foo() = default;
    explicit foo(BarRef value)
        : ref(value)
    {
        using type = typename std::remove_reference<BarRef>::type;
        constexpr auto b = std::is_const<type>::value;
        std::cout << b << std::endl;
    }
    BarRef ref;
};

template<typename T>
struct bar
{
    bar()
        : value_(0)
    {}

    auto func()
    {
        std::cout << "void func() ===" << std::endl;
        using type = decltype(*this);
        using type2 = typename std::remove_reference<type>::type;
        constexpr auto value = std::is_const<type2>::value;
        value_ = 1;
        auto result = foo<type>(*this);
        using foo_type = decltype(foo<type>::ref);
        std::cout << "void func() ===" << std::endl;
        return result;
    }

    auto func() const
    {
        std::cout << "void func() const ===" << std::endl;
        using type = decltype(*this);
        using type2 = typename std::remove_reference<type>::type;
        constexpr auto value = std::is_const<type2>::value;
        auto result = foo<type>(*this);
        using foo_type = decltype(foo<type>::ref);
        std::cout << "void func() const ===" << std::endl;
        return result;
    }
    T value_;
};

int main()
{
    {
        using bar_type = bar<int>;
        bar_type b1;
        const bar_type b2;
        auto ret1 = b1.func();
        auto ret2 = b2.func();
    }
    {
        constexpr auto dim = is_n_dimensional_vector<1, 3, 3>::value;
    }
    {
        std::cout << "=== column_major_order" << std::endl;
        using Matrix = Matrix<float, 2, 3, column_major_order>;
        Matrix m({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f});
        for(Matrix::size_type i = 0; i < Matrix::size(); i++){
            auto row = Matrix::row_subscript(i);
            auto col = Matrix::column_subscript(i);
            std::cout << "index " << i << " => (" << row << ", " << col << ") = " << m(row, col) << std::endl;
        }
        std::cout << std::endl;
    }
    {
        std::cout << "=== row_major_order" << std::endl;
        using Matrix = Matrix<float, 2, 3, row_major_order>;
        Matrix m({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f });
        for(Matrix::size_type i = 0; i < Matrix::size(); i++){
            auto row = Matrix::row_subscript(i);
            auto col = Matrix::column_subscript(i);
            std::cout << "index " << i << " => (" << row << ", " << col << ") = " << m(row, col) << std::endl;
        }
        std::cout << std::endl;
    }

    {
        using Matrix = Matrix<float, 2, 2, column_major_order>;
        //using Matrix = Matrix<float, 2, 2, row_major_order>;
        Matrix ma({ 1.0f, 2.0f, 3.0f, 4.0f });
        Matrix mb({ 1.0f, 2.0f, 3.0f, 4.0f });
        Matrix mc;

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

        ma(1, 1) = 2.0f;
        auto elem = ma(1, 1);
        int a = 1;
    }
    {
        //using vector = Matrix<float, 1, 2, row_major_order>;
        //using Matrix = Matrix<float, 2, 2, row_major_order>;
        using vector = Matrix<float, 2, 1, column_major_order>;
        using Matrix = Matrix<float, 2, 2, column_major_order>;

        vector va({ 1.0f, 2.0f });
        Matrix m({ 1.0f, 2.0f, 3.0f, 4.0f });
        vector v;
        v = m * va;
        //v = va * m;
        std::cout << v << std::endl;
    }
    {
        //using vector = Matrix<float, 1, 2>;
        using vector = Matrix<float, 2, 1>;
        vector a({ 1.0f, 2.0f });
        vector b({ 2.0f, 3.0f });
        auto dot = dot_product(a, b);
        std::cout << dot << std::endl;
    }
    {
        using vector = Matrix<float, 1, 2>;
        vector a({ 1.0f, 2.0f });
        vector b({ 4.0f, 5.0f });
        auto cross = cross_product(a, b);
    }
    {
        using vector = Matrix<float, 3, 1>;
        vector a({ 1.0f, 2.0f, 3.0f });
        vector b({ 4.0f, 5.0f, 6.0f });
        auto cross = cross_product(a, b);
    }
    {
        using RMatrix = Matrix<float, 2, 2, row_major_order>;
        using CMatrix = Matrix<float, 2, 2, column_major_order>;

        RMatrix ra;
        RMatrix rb;
        ra *= rb;
        ra = ra * rb;
        ra += rb;

        CMatrix ca;
        CMatrix cb;
        ca *= cb;
        ca = ca * cb;
        ca += cb;
    }
    {
        //using Matrix = Matrix<float, 2, 2, row_major_order>;
        using Matrix = Matrix<float, 2, 2, column_major_order>;
        Matrix m({ 1.0f, 2.0f, 3.0f, 4.0f });
        auto ret = m.trace();
        std::cout << ret << std::endl;
    }
#if defined(ENABLE_BLOCK_TEST)
    {
        using Matrix2 = Matrix<float, 2, 2, column_major_order>;
        using Matrix3 = Matrix<float, 3, 3, column_major_order>;
        Matrix2 m2a({ 1.0f, 2.0f, 3.0f, 4.0f });
        Matrix3 m3a({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f });

        Matrix2 m;
        m = m3a.block<2, 2>(1, 1);
        std::cout << "m3a" << std::endl;
        std::cout << m3a << std::endl;
        std::cout << "m3a.block<2, 2>(1, 1)" << std::endl;
        std::cout << m << std::endl;

        m3a.block<2, 2>(1, 1) = m2a;
        std::cout << "m2a" << std::endl;
        std::cout << m2a << std::endl;
        std::cout << "m3a.block<2, 2>(1, 1) = m2a" << std::endl;
        std::cout << m3a << std::endl;
    }
#endif
    return 0;
}
