#include <iostream>
#include <cassert>
#include <typeinfo>
#include "vector.h"
#include "matrix.h"

template<typename T>
void vector_test()
{
    using value_type = T;
    using vector = mymath::vector<value_type>;
    std::cout << "=== [Test] vector<" << typeid(value_type).name() << "> ===" << std::endl;
    {
        std::cout << "<< v = va + vb >>" << std::endl;
        vector va({ static_cast<value_type>(1), static_cast<value_type>(2) });
        vector vb({ static_cast<value_type>(3), static_cast<value_type>(4) });
        vector v(va + vb);
        std::cout << "va: " << va << std::endl;
        std::cout << "vb: " << vb << std::endl;
        std::cout << "v : " << v << std::endl;
        std::cout << std::endl;
    }
    {
        std::cout << "<< v = va - vb >>" << std::endl;
        vector va({ static_cast<value_type>(1), static_cast<value_type>(2) });
        vector vb({ static_cast<value_type>(3), static_cast<value_type>(4) });
        vector v(va - vb);
        std::cout << "va: " << va << std::endl;
        std::cout << "vb: " << vb << std::endl;
        std::cout << "v : " << v << std::endl;
        std::cout << std::endl;
    }
    {
        std::cout << "<< v = va * 2 >>" << std::endl;
        vector va({ static_cast<value_type>(1), static_cast<value_type>(2) });
        vector v(va * static_cast<value_type>(2));
        std::cout << "va: " << va << std::endl;
        std::cout << "v : " << v << std::endl;
        std::cout << std::endl;
    }
    {
        std::cout << "<< v = 3 * va >>" << std::endl;
        vector va({ static_cast<value_type>(1), static_cast<value_type>(2) });
        vector v(static_cast<value_type>(3) * va);
        std::cout << "va: " << va << std::endl;
        std::cout << "v : " << v << std::endl;
        std::cout << std::endl;
    }
    {
        std::cout << "<< v = va / 2 >>" << std::endl;
        vector va({ static_cast<value_type>(8), static_cast<value_type>(3) });
        vector v(va / static_cast<value_type>(2));
        std::cout << "va: " << va << std::endl;
        std::cout << "v : " << v << std::endl;
        std::cout << std::endl;
    }
    {
        std::cout << "<< v = 3 * (va + vb) / 2 >>" << std::endl;
        vector va({ static_cast<value_type>(1), static_cast<value_type>(2) });
        vector vb({ static_cast<value_type>(3), static_cast<value_type>(4) });
        vector v(static_cast<value_type>(3) * (va + vb) / static_cast<value_type>(2));
        std::cout << "va: " << va << std::endl;
        std::cout << "vb: " << vb << std::endl;
        std::cout << "v : " << v << std::endl;
        std::cout << std::endl;
    }
}

template<typename T>
void matrix_test()
{
    using value_type = T;
    using matrix = mymath::matrix<value_type>;
    std::cout << "=== [Test] matrix<" << typeid(value_type).name() << "> ===" << std::endl;
    {
        std::cout << "<< m = 2 * (ma + mb) + (ma - mb) * 3 >>" << std::endl;
        matrix ma({ static_cast<value_type>(0), static_cast<value_type>(1),
                    static_cast<value_type>(2), static_cast<value_type>(3) });
        matrix mb({ static_cast<value_type>(4), static_cast<value_type>(5),
                    static_cast<value_type>(6), static_cast<value_type>(7) });
        auto exp = static_cast<value_type>(2) * (ma + mb) + (ma - mb) * static_cast<value_type>(3);
        matrix m(exp);
        std::cout << "ma: " << std::endl << ma << std::endl;
        std::cout << "mb: " << std::endl << mb << std::endl;
        std::cout << "m : " << std::endl << m  << std::endl;
        std::cout << std::endl;
    }
}

int main()
{
    vector_test<float>();
    vector_test<double>();
    vector_test<long double>();
    vector_test<std::int16_t>();
    vector_test<std::int32_t>();
    vector_test<std::int64_t>();

    matrix_test<float>();

    return 0;
}