#include <iostream>
#include <cassert>
#include <typeinfo>
#include "vector.h"

template<typename T>
void Test()
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

int main()
{
    Test<float>();
    Test<double>();
    Test<long double>();
    Test<std::int16_t>();
    Test<std::int32_t>();
    Test<std::int64_t>();

    return 0;
}