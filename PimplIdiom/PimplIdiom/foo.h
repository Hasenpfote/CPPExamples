#pragma once
#include <memory>
#include <string>

class Foo final
{
public:
    Foo();
    ~Foo();
    void Print(const std::string& message);

private:
    class Impl;
    std::unique_ptr<Impl> pimpl;
};