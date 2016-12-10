#include <iostream>
#include <iomanip>
#include <bitset>
#include <cassert>
#include "fp.h"

template<typename T>
void compare(T a, T b, T abs_tol, T rel_tol)
{
    auto eq = IsApproximatelyEqualTo(a, b, abs_tol, rel_tol);
    auto gt = IsDefinitelyGreaterThan(a, b, abs_tol, rel_tol);
    auto gte = IsGreaterThanOrApproximatelyEqualTo(a, b, abs_tol, rel_tol);
    auto lt = IsDefinitelyLessThan(a, b, abs_tol, rel_tol);
    auto lte = IsLessThanOrApproximatelyEqualTo(a, b, abs_tol, rel_tol);

    std::cout << std::scientific << "a = " << a << std::endl;
    std::cout << std::scientific << "b = " << b << std::endl;
    std::cout << std::boolalpha << "a == b: " << eq << std::endl;
    std::cout << std::boolalpha << "a >  b: " << gt << std::endl;
    std::cout << std::boolalpha << "a >= b: " << gte << std::endl;
    std::cout << std::boolalpha << "a <  b: " << lt << std::endl;
    std::cout << std::boolalpha << "a <= b: " << lte << std::endl;
    std::cout << std::endl;

    assert((eq) ? (!gt && gte && !lt && lte) : true);
    assert((!eq && gt) ? (gte && !lt && !lte) : true);
    assert((!eq && lt) ? (!gt && !gte && lte) : true);
}

int main()
{
    const float abs_tol = 1e-10f;
    const float rel_tol = std::numeric_limits<float>::epsilon();
    float a, b;

    a = -1.000000f;
    b = -1.000001f;
    compare(a, b, abs_tol, rel_tol);
    a =  0.000000f;
    b = -0.000001f;
    compare(a, b, abs_tol, rel_tol);
    a =  1.000000f;
    b =  0.999999f;
    compare(a, b, abs_tol, rel_tol);
    a = 10.000000f;
    b =  9.999999f;
    compare(a, b, abs_tol, rel_tol);
    a = 100.00000f;
    b =  99.99999f;
    compare(a, b, abs_tol, rel_tol);
    a = 1000.0000f;
    b =  999.9999f;
    compare(a, b, abs_tol, rel_tol);
    a = 10000.000f;
    b =  9999.999f;
    compare(a, b, abs_tol, rel_tol);
    a = 100000.00f;
    b =  99999.99f;
    compare(a, b, abs_tol, rel_tol);

    // is close to zero.
    {
        a = 0.0000000001f;
        b = 0.0f;
        std::cout << std::boolalpha << "AreCloseWithinAbsoluteTolerance: " << AreCloseWithinAbsoluteTolerance(a, b, abs_tol) << std::endl;
        std::cout << std::boolalpha << "AreCloseWithinRelativeTolerance: " << AreCloseWithinRelativeTolerance(a, b, rel_tol) << std::endl;
        std::cout << std::boolalpha << "IsCloseToZero: " << IsCloseToZero(a, abs_tol) << std::endl;
    }
    // is close to one.
    {
        a = 1.0000001f;
        b = 1.0f;
        std::cout << std::boolalpha << "IsCloseToOne: " << IsApproximatelyEqualTo(a, b, abs_tol, rel_tol) << std::endl;
    }
    return 0;
}