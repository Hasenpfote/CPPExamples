#include <iostream>
#include <cassert>
#include "vector2.h"

int main()
{
    {
        std::cout << "=== vector2<float> ===" << std::endl;
        using vector2 = mymath::vector2<float>;
        {
            std::cout << "<< v = va + vb >>" << std::endl;
            vector2 va(1.0f, 2.0f);
            vector2 vb(3.0f, 4.0f);
            vector2 v(va + vb);
            std::cout << "va: " << va << std::endl;
            std::cout << "vb: " << vb << std::endl;
            std::cout << "v : " << v  << std::endl;
            std::cout << std::endl;
        }
        {
            std::cout << "<< v = va - vb >>" << std::endl;
            vector2 va(1.0f, 2.0f);
            vector2 vb(3.0f, 4.0f);
            vector2 v(va - vb);
            std::cout << "va: " << va << std::endl;
            std::cout << "vb: " << vb << std::endl;
            std::cout << "v : " << v << std::endl;
            std::cout << std::endl;
        }
        {
            std::cout << "<< v = va * 2 >>" << std::endl;
            vector2 va(1.0f, 2.0f);
            vector2 v(va * 2.0f);
            std::cout << "va: " << va << std::endl;
            std::cout << "v : " << v << std::endl;
            std::cout << std::endl;
        }
        {
            std::cout << "<< v = 3 * va >>" << std::endl;
            vector2 va(1.0f, 2.0f);
            vector2 v(3.0f * va);
            std::cout << "va: " << va << std::endl;
            std::cout << "v : " << v << std::endl;
            std::cout << std::endl;
        }
        {
            std::cout << "<< v = va / 2 >>" << std::endl;
            vector2 va(8.0f, 3.0f);
            vector2 v(va / 2.0f);
            std::cout << "va: " << va << std::endl;
            std::cout << "v : " << v << std::endl;
            std::cout << std::endl;
        }
        {
            std::cout << "<< v = 3 * (va + vb) / 2 >>" << std::endl;
            vector2 va(1.0f, 2.0f);
            vector2 vb(3.0f, 4.0f);
            vector2 v(3.0f * (va + vb) / 2.0f);
            std::cout << "va: " << va << std::endl;
            std::cout << "vb: " << vb << std::endl;
            std::cout << "v : " << v << std::endl;
            std::cout << std::endl;
        }
    }
    {
        std::cout << "=== vector2<std::int32_t> ===" << std::endl;
        using vector2 = mymath::vector2<std::int32_t>;
        {
            std::cout << "<< v = va + vb >>" << std::endl;
            vector2 va(1, 2);
            vector2 vb(3, 4);
            vector2 v(va + vb);
            std::cout << "va: " << va << std::endl;
            std::cout << "vb: " << vb << std::endl;
            std::cout << "v : " << v << std::endl;
            std::cout << std::endl;
        }
        {
            std::cout << "<< v = va - vb >>" << std::endl;
            vector2 va(1, 2);
            vector2 vb(3, 4);
            vector2 v(va - vb);
            std::cout << "va: " << va << std::endl;
            std::cout << "vb: " << vb << std::endl;
            std::cout << "v : " << v << std::endl;
            std::cout << std::endl;
        }
        {
            std::cout << "<< v = va * 2 >>" << std::endl;
            vector2 va(1, 2);
            vector2 v(va * 2);
            std::cout << "va: " << va << std::endl;
            std::cout << "v : " << v << std::endl;
            std::cout << std::endl;
        }
        {
            std::cout << "<< v = 3 * va >>" << std::endl;
            vector2 va(1, 2);
            vector2 v(3 * va);
            std::cout << "va: " << va << std::endl;
            std::cout << "v : " << v << std::endl;
            std::cout << std::endl;
        }
        {
            std::cout << "<< v = va / 2 >>" << std::endl;
            vector2 va(8, 3);
            vector2 v(va / 2);
            std::cout << "va: " << va << std::endl;
            std::cout << "v : " << v << std::endl;
            std::cout << std::endl;
        }
        {
            std::cout << "<< v = 3 * (va + vb) / 2 >>" << std::endl;
            vector2 va(1, 2);
            vector2 vb(3, 4);
            vector2 v(3 * (va + vb) / 2);
            std::cout << "va: " << va << std::endl;
            std::cout << "vb: " << vb << std::endl;
            std::cout << "v : " << v << std::endl;
            std::cout << std::endl;
        }
    }
    return 0;
}
