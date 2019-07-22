#include <iostream>
#include <vector>

class Foo
{
public:
    Foo()
        : value()
    {
        std::cout << "Foo()" << std::endl;
    }
#if 0
    Foo(const Foo&) = default;
    Foo(Foo&& foo) = default;
#else
    //
    Foo(const Foo& foo)
    {
        std::cout << "Foo(const Foo&)" << std::endl;
        value = foo.value;
    }
    //
    Foo(Foo&& foo)
    {
        std::cout << "Foo(Foo&&)" << std::endl;
        value = foo.value;
    }
#endif
    //
    ~Foo()
    {
        std::cout << "~Foo()" << std::endl;
    }
    explicit Foo(int value)
        : value(value)
    {
        std::cout << "Foo(int)" << std::endl;
    }
    int value;
};

static Foo gfoo1 = Foo(50);
static Foo gfoo2 = Foo(60);

Foo rvo1()
{
    return Foo(3);
}

Foo rvo2(bool cond)
{
    return (cond)? Foo(3) : Foo(4);
}

Foo rvo3(bool cond)
{
    return Foo((cond)? gfoo1 : gfoo2);
}

int main()
{
    std::cout << "--- start." << std::endl;
    {
        std::cout << "--- rvo1" << std::endl;
        auto foo = rvo1();
        (void)foo;
        std::cout << "--- scope end." << std::endl;
    }
    std::cout << std::endl;
    {
        std::cout << "--- rvo2" << std::endl;
        auto foo1 = rvo2(true);
        (void)foo1;
        auto foo2 = rvo2(false);
        (void)foo2;
        std::cout << "--- scope end." << std::endl;
    }
    std::cout << std::endl;
    {
        std::cout << "--- rvo3" << std::endl;
        auto foo1 = rvo3(true);
        std::cout << "--- " << foo1.value << std::endl;
        auto foo2 = rvo3(false);
        std::cout << "--- " << foo2.value << std::endl;
        std::cout << "--- scope end." << std::endl;
    }
    std::cout << std::endl;
    std::cout << "--- done." << std::endl;
    return 0;
}