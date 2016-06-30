#pragma once

class IUnknownService
{
public:
    IUnknownService() = default;
    virtual ~IUnknownService() = default;
    virtual void DoSomething()
    {
        std::cout << __func__ << std::endl;
    }
};