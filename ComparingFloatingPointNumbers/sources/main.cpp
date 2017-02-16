#include <iostream>
#include <iomanip>
#include <bitset>
#include <cassert>
#include "fp_comparison.h"

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

template<typename T>
void compare2(T a, T b, T abs_tol, T rel_tol)
{
    auto b1 = AreCloseWithinAbsoluteTolerance(a, b, abs_tol);
    auto b2 = AreCloseWithinRelativeTolerance(a, b, rel_tol);
    std::cout << std::scientific << "a=" << a << " , b=" << b << std::endl;
    std::cout << std::boolalpha << "AreCloseWithinAbsoluteTolerance: " << b1 << std::endl;
    std::cout << std::boolalpha << "AreCloseWithinRelativeTolerance: " << b2 << std::endl;
}

void test1()
{
    // for float.
    const float abst = 1e-7f;
    const float relt = 1e-6f;   // 1e-5f > rel > 1e-6f

    std::cout << "case 1-a" << std::endl;
    compare2(0.000000f, 0.0000001f, abst, relt);
    compare2(1.000000f, 1.000001f, abst, relt);
    compare2(10.00000f, 10.00001f, abst, relt);
    compare2(100.0000f, 100.0001f, abst, relt);
    compare2(1000.000f, 1000.001f, abst, relt);
    compare2(10000.00f, 10000.01f, abst, relt);
    compare2(100000.0f, 100000.1f, abst, relt);     // x

    std::cout << "case 2-a" << std::endl;
    compare2(1.000000f, 0.999999f, abst, relt);     // x
    compare2(10.00000f, 9.999990f, abst, relt);
    compare2(100.0000f, 99.99990f, abst, relt);
    compare2(1000.000f, 999.9990f, abst, relt);
    compare2(10000.00f, 9999.990f, abst, relt);
    compare2(100000.0f, 99999.90f, abst, relt);     // x
}

int main()
{
    test1();

    return 0;
}