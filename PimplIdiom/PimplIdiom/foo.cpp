#include <iostream>
#include "foo.h"

class Foo::Impl
{
public:
    void Print(const std::string& message)
    {
        std::cout << __func__ << ": "  << message << std::endl;
    }
};

Foo::Foo() : pimpl(std::make_unique<Impl>())
{
}

Foo::~Foo() = default;

void Foo::Print(const std::string& message)
{
    pimpl->Print(message);
}