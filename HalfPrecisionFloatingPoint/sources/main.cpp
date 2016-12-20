#include <iostream>
#include <iomanip>
#include <cassert>
#include "fp_conversion.h"

int main()
{
    const float s = 1.234000f;
    auto h1 = ConvertSingleToHalf(s);
    auto s1 = ConvertHalfToSingle(h1);

    std::cout << s << std::endl;
    std::cout << h1 << std::endl;
    std::cout << s1 << std::endl;

    return 0;
}