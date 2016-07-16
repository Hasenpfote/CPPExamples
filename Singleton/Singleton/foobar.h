#pragma once
#include <iostream>
#include <vector>
#include "singleton.h"

class Foo final : public example::Singleton<Foo>
{
    friend class example::Singleton<Foo>;

public:
    using Vector = std::vector<int>;

private:
    Foo()
    {
        std::cout << __func__ << ": " << std::endl;
    }
    explicit Foo(const Vector& v)
    {
        std::cout << __func__ << ": const Vector& v" << std::endl;
    }
    explicit Foo(Vector&& v)
    {
        std::cout << __func__ << ": Vector&& v" << std::endl;
    }
    Foo(int value1, int value2, int value3)
    {
        std::cout << __func__ << ": int value1, int value2, int value3" << std::endl;
    }

public:
    ~Foo()
    {
        std::cout << __func__ << std::endl;
    }

public:
    void Func()
    {
        std::cout << __func__ << std::endl;
    }
private:
};