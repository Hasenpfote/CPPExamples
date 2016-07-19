#pragma once
#include <iostream>
#include "singleton.h"

class Foo final : public example::Singleton<Foo>
{
    friend class example::Singleton<Foo>;

private:
    Foo()
    {
        std::cout << __func__ << std::endl;
    }
public:
    ~Foo()
    {
        std::cout << __func__ << std::endl;
    }
    void DoSomething()
    {
        std::cout << __func__ << std::endl;
    }
};
